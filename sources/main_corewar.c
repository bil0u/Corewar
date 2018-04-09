/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/09 08:00:22 by upopee           ###   ########.fr       */
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

static void	init_data(t_cwdata *env)
{
	env->control.to_die = CYCLE_TO_DIE;
	env->control.winner = env->players[env->nb_players - 1].player_no;
	env->control.nb_processes = env->control.tot_processes;
	env->cpu.memory = env->arena;
	env->cpu.data.last_alive = &(env->control.winner);
	env->cpu.data.nb_processes = &(env->control.nb_processes);
	env->cpu.data.tot_processes = &(env->control.tot_processes);
	print_memory(env, "mem");
	print_registers(NULL, "reg");
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
		ft_lstdel(&(env->players[i].processes), &ft_delcontent);
	}
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
	t_player	*p;
	int			curr_p;

	breakpoint = env->control.nb_cycles;
	while (env->control.to_die && env->control.nb_processes && ++cpu->tick)
	{
		curr_p = -1;
		while (++curr_p < env->nb_players)
		{
			if ((p = env->players + curr_p) && p->pending)
			{
				print_memory(env, "mem");
				flags & CWF_SLOW ? usleep(env->control.sleep_us) : (void)0;
				exec_or_wait(cpu, p, (t_process *)p->pending->content);
			}
			p->pending = p->pending->next ? p->pending->next : p->processes;
		}
		if (cpu->tick == env->control.last_check + env->control.to_die)
			kill_quiet_processes(env);
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
