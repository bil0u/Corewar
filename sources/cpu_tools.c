/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:21:21 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 16:30:47 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

void	init_cpu(t_vcpu *cpu)
{
	ft_bzero(cpu, sizeof(*cpu));
}

void 	load_process(t_vcpu *cpu, uint8_t *process_regs, uint8_t *process_pc)
{
	cpu->registers = process_regs;
	cpu->pc = process_pc;
}
