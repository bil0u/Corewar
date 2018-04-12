/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/12 06:59:01 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "cpu.h"
#include "corewar.h"
#include "corewar_verbose.h"

/*
** -- INITIALIZE THE MAIN ENVIRONMENT AND THE LOG WINDOWS
*/

static int	init_env(int argc, char **argv, t_cwdata *env)
{
	ft_bzero(env, sizeof(*env));
	if (check_argv(argc, argv, env) != SUCCESS)
		return (FAILURE);
	new_logwindow("inf", WF_KEEP | WF_CLOSE);
	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);
	new_logwindow("chp", WF_KEEP | WF_CLOSE);
	return (SUCCESS);
}

/*
** -- INITIALIZE THE NEEDED ELEMENTS FOR LAUNCHING THE GAME
*/

static void	init_data(t_cwdata *env)
{
	env->control.to_die = CYCLE_TO_DIE;
	env->control.winner = env->players[env->nb_players - 1].player_no;
	env->control.nb_processes = env->control.tot_processes;
	env->cpu.memory = env->arena;
	env->cpu.data.last_alive = &(env->control.winner);
	env->cpu.data.nb_lives = &(env->control.nb_lives);
	env->cpu.data.nb_processes = &(env->control.nb_processes);
	env->cpu.data.tot_processes = &(env->control.tot_processes);
	env->cpu.data.processes_stack = &(env->processes);
	if (env->control.sleep_us > 0)
		env->control.sleep_us = (1000000 /
								(env->control.sleep_us * env->nb_players));
	print_memory(env->arena, env->processes, "mem");
	// print_registers(NULL, NULL, "reg");
	sleep(1);
}

/*
** -- FREE ALLOCATED ELEMENTS AND DECLARE WINNER
*/

static void	end_game(t_cwdata *env)
{
	char	*winner_name;
	uint8_t	winner;
	int		i;

	print_memory(env->arena, env->processes, "mem");
	i = -1;
	winner = env->control.winner;
	winner_name = NULL;
	while (++i < env->nb_players)
	{
		if (env->players[i].player_no == winner)
			winner_name = env->players[i].header.prog_name;
	}
	ft_lstdel(&(env->processes), &ft_delcontent);
	ft_printf(CW_WINNER_IS, winner, winner_name);
	log_this("chp", 0, CW_WINNER_IS, winner, winner_name);
}

/*
** -- RUN THE CPU FOR A SET CYCLES NUMBER OR UNTIL A WINNER IS FOUND,
**    DEPENDING ON GIVEN OPTIONS
*/

static void		run_cpu(t_cwdata *env, t_pcontrol *ct,
								t_vcpu *cpu, uint16_t flags)
{
	uint64_t	breakpoint;
	t_list		*pending;
	t_process	*process;
	t_player	*player;

	breakpoint = ct->nb_cycles;
	while (ct->nb_processes && ct->to_die && ++cpu->tick)
	{
		log_this("inf", 0, INF_MSG, cpu->tick, ct->nb_processes, ct->nb_lives,
			ct->to_die, ct->last_check, ct->nb_checks, MAX_CHECKS);
		pending = env->processes;
		while (pending != NULL)
		{
			process = (t_process *)pending->content;
			player = env->players + env->p_indexes[process->player_no - 1];
			exec_or_wait(cpu, player, process);
			flags & CWF_SLOW ? usleep(ct->sleep_us) : (void)0;
			pending = pending->next;
		}
		if (cpu->tick == ct->last_check + ct->to_die)
			refresh_process_status(env, ct);
		if (cpu->tick == breakpoint)
			if (dump_stop(env, flags, &breakpoint) == TRUE)
				break ;
	}
}

int			main(int argc, char **argv)
{
	t_cwdata	env;

	if (init_env(argc, argv, &env) != SUCCESS)
		return (err_msg(CWE_HELP));
	load_players(&env, &(env.players[0]));
	init_data(&env);
	run_cpu(&env, &env.control, &env.cpu, env.control.flags);
	end_game(&env);
	return (SUCCESS);
}
