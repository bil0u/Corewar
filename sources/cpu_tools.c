/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:21:21 by upopee            #+#    #+#             */
/*   Updated: 2018/03/05 04:33:02 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

void		init_cpu(t_vcpu *cpu, uint8_t *memory)
{
	ft_bzero(cpu, sizeof(*cpu));
	cpu->vm_memory = memory;
}

void 		load_process(t_vcpu *cpu, uint8_t *p_regs, uint64_t p_pc)
{
	cpu->registers = p_regs;
	cpu->pc = p_pc;
}
