/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/08 11:43:22 by upopee           ###   ########.fr       */
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
	ft_bzero(env, sizeof(*env));
	env->control.cycles_to_die = CYCLE_TO_DIE;
	env->cpu.memory = env->arena;
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
	while (++cpu->tick && env->control.cycles_to_die > 0)
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
		if (cpu->tick == env->control.last_check + env->control.cycles_to_die)
			kill_quiet_processes(env);
		if (cpu->tick == breakpoint)
			if (dump_stop(env, flags, &breakpoint) == TRUE)
				break ;
	}
}

int			main(int argc, char **argv)
{
	t_cwdata	env;

	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);
	new_logwindow("chp", WF_KEEP | WF_CLOSE);

	init_env(&env);
	if (check_argv(argc, argv, &env) != SUCCESS)
		return (err_msg(CWE_HELP));
	load_players(&env);
	print_memory(&env, "mem");
	sleep(1);
	run_cpu(&env, &env.cpu, env.control.flags);
	print_memory(&env, "mem");
	return (SUCCESS);
}
