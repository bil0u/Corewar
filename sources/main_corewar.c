/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/08 14:11:21 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "cpu.h"
#include "corewar.h"
#include "corewar_verbose.h"

static void	init_env(t_cwdata *env)
{
	env->control.to_die = CYCLE_TO_DIE;
	env->control.nb_processes = env->nb_players;
	env->control.winner = env->players[env->nb_players - 1].player_no;
	env->cpu.memory = env->arena;
	env->cpu.data.last_alive = &(env->control.winner);
}

static int	dump_stop(t_cwdata *env, uint16_t flags, uint64_t *breakpoint)
{
	print_memory(env, NULL);
	if (flags & CWF_DUMP)
		return (TRUE);
	sleep(3);
	*breakpoint += env->control.nb_cycles;
	return (FALSE);
}

static void	run_cpu(t_cwdata *env, t_vcpu *cpu, uint16_t flags)
{
	uint64_t	breakpoint;
	t_list		*p;
	int			curr_player;

	breakpoint = env->control.nb_cycles;
	while (env->control.to_die > 0 && env->control.nb_processes > 0 && ++cpu->tick)
	{
		curr_player = -1;
		while (++curr_player < env->nb_players)
			if ((p = (env->players + curr_player)->pending) != NULL)
			{
				load_process((t_process *)(p->content), cpu);
				exec_instruction(cpu);
				print_memory(env, "mem");
				print_registers((t_process *)(p->content), "reg");
				p = p->next ? p->next : (env->players + curr_player)->processes;
				flags & CWF_SLOW ? sleep(1) : (void)0;
			}
		if (cpu->tick == env->control.last_check + env->control.to_die)
			kill_quiet_processes(env);
		if (cpu->tick == breakpoint)
			if (dump_stop(env, flags, &breakpoint) == TRUE)
				break ;
	}
}

static void	end_game(t_cwdata *env)
{
	char	*winner_name;
	uint8_t	winner;
	int		i;

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

int			main(int argc, char **argv)
{
	t_cwdata	env;

	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);
	new_logwindow("chp", WF_KEEP | WF_CLOSE);

	ft_bzero(&env, sizeof(env));
	if (check_argv(argc, argv, &env) != SUCCESS)
		return (err_msg(CWE_HELP));
	load_players(&env);
	init_env(&env);
	print_memory(&env, "mem");
	sleep(1);
	run_cpu(&env, &env.cpu, env.control.flags);
	print_memory(&env, "mem");
	end_game(&env);
	return (SUCCESS);
}
