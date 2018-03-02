/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 04:01:18 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu.h"

void	no_instr(t_vcpu *cpu)
{
	(void)cpu;
}

void	live_instr(t_vcpu *cpu)
{
	ft_printf("Player %d is alive !\n", CPU_ARG_NO(cpu, 0).u32);
}

void	load_instr(t_vcpu *cpu)
{
	(void)cpu;
}
