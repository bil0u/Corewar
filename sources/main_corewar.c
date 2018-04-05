/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 19:45:37 by upopee           ###   ########.fr       */
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
	env->cpu.memory = env->arena;
}

static void	load_process(t_process *p, t_vcpu *cpu)
{
	cpu->pc = &p->pc;
	cpu->timer = &p->timer;
	cpu->carry = &p->carry;
	cpu->registers = p->registers;
	cpu->curr_instruction = NULL;
}

static void	run_cpu(t_cwdata *env, uint32_t nb_cycles, uint16_t flags)
{
	t_player	*p;
	uint32_t	delta_ticks;
	uint8_t		curr;

	delta_ticks = 0;
	while (env->cpu.tick - delta_ticks < nb_cycles)
	{
		curr = 0;
		while (curr < env->nb_players)
		{
			//	print_memory(&env->cpu, BIS_SET(flags, CWF_SLOW));
			p = env->players + curr;
			p->pending = p->pending ? p->pending->next : p->processes;
			if (p->pending)
			{
				load_process((t_process *)(p->pending->content), &env->cpu);
				exec_instruction(&env->cpu);
			}
			print_registers(&env->cpu, BIS_SET(flags, CWF_SLOW));
			++curr;
		}
		BIS_SET(flags, CWF_DUMP | CWF_SDMP) ? (void)0 : ++delta_ticks;
		BIS_SET(flags, CWF_SLOW) ? sleep(1) : (void)0;
		++(env->cpu.tick);
	}
	BIS_SET(flags, CWF_SDMP) ? run_cpu(env, nb_cycles, flags) : (void)0;
}

int			main(int argc, char **argv)
{
	t_cwdata	env;

	// new_logwindow("mem", WF_KEEP | WF_CLOSE);
	// new_logwindow("reg", WF_KEEP | WF_CLOSE);
	// new_logwindow("ins", WF_KEEP | WF_CLOSE);
	// new_logwindow("chp", WF_KEEP | WF_CLOSE);

	init_env(&env);
	if (check_argv(argc, argv, &env) != SUCCESS)
		return (FAILURE);
	load_players(&env);
	run_cpu(&env, env.nb_cycles, env.flags);
	return (SUCCESS);
}
