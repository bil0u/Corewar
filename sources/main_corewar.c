/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 15:03:15 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"
#include "corewar_types.h"
#include "corewar.h"
#include "corewar_verbose.h"

static void	init_env(t_cwdata *env)
{
	ft_bzero(env, sizeof(*env));
	env->cpu.memory = env->arena;
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
		return (FAILURE);

	uint32_t	registers[REG_NUMBER];
	ft_bzero(registers, sizeof(*registers) * REG_NUMBER);
	env.cpu.registers = registers;

	run_cpu(&env.cpu, env.flags, env.nb_cycles);
	return (SUCCESS);
}
