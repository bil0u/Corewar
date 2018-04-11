/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/11 21:52:07 by upopee           ###   ########.fr       */
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
	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);
	new_logwindow("chp", WF_KEEP | WF_CLOSE);
	return (SUCCESS);
}

/*
** -- INITIALIZE THE NEEDED ELEMENTS FOR LAUNCHING THE GAME
*/

static void	init_data(t_cwdata *e)
{
	e->control.to_die = CYCLE_TO_DIE;
	e->control.winner = e->players[e->nb_players - 1].player_no;
	e->control.nb_processes = e->control.tot_processes;
	e->cpu.memory = e->arena;
	e->cpu.data.last_alive = &(e->control.winner);
	e->cpu.data.nb_processes = &(e->control.nb_processes);
	e->cpu.data.tot_processes = &(e->control.tot_processes);
	e->cpu.data.processes_stack = &(e->processes);
	//e->control.l_flags =
	if (e->control.sleep_us > 0)
		e->control.sleep_us = (1000000 / (e->control.sleep_us * e->nb_players));
	print_memory(e, "mem");
	print_registers(NULL, NULL, "reg");
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

	print_memory(env, "mem");
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

static void		run_cpu(t_cwdata *env, t_vcpu *cpu, uint16_t flags)
{
	uint64_t	breakpoint;
	t_list		*pending;
	t_process	*process;
	t_player	*player;

	breakpoint = env->control.nb_cycles;
	while (env->control.to_die && env->control.nb_processes && ++cpu->tick)
	{
		pending = env->processes;
		while (pending != NULL)
		{
			process = (t_process *)pending->content;
			player = env->players + env->p_indexes[process->player_no - 1];
			flags & CWF_SLOW ? usleep(env->control.sleep_us >> 1) : (void)0;
			print_memory(env, "mem");
			flags & CWF_SLOW ? usleep(env->control.sleep_us >> 1) : (void)0;
			exec_or_wait(cpu, player, process);
			pending = pending->next;
		}
		if (cpu->tick == env->control.last_check + env->control.to_die)
			refresh_process_status(env);
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
	run_cpu(&env, &env.cpu, env.control.flags);
	end_game(&env);
	return (SUCCESS);
}
