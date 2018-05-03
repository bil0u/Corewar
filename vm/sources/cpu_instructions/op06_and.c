/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op06_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:20:43 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 06:30:25 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

int		and_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[2]);
	decode_arg(CPU_MEM, p, (CPU_OPBC >> 6) & 3, CPU_ARG);
	decode_arg(CPU_MEM, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1);
	r[r_dst - 1] = CPU_ARG[0] & CPU_ARG[1];
	p->carry = (r[r_dst - 1] == 0);
	if (INS_DEB)
		log_this(IDW, D_AND, IDA,
			CPU_ARG[0], CPU_ARG[1], r[r_dst - 1], r_dst, p->carry);
	if (INS_VERB)
		ft_printf(V_AND, IVA, CPU_ARG[0], CPU_ARG[1], r_dst);
	return (0);
}
