/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:24:22 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 06:30:35 by upopee           ###   ########.fr       */
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

int		ldi_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint16_t	pc_src;
	int16_t		index;
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[2]);
	decode_arg(CPU_MEM, p, (CPU_OPBC >> 6) & 3, CPU_ARG);
	decode_arg(CPU_MEM, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1);
	index = TOI16((TOI32(CPU_ARG[0]) + TOI32(CPU_ARG[1])) % IDX_MOD);
	pc_src = jump_to(p->pc, index);
	secure_fetch(CPU_MEM, pc_src, r + r_dst - 1, REG_SIZE);
	INS_DEB ? log_this(IDW, D_LDI, IDA,
		r[r_dst - 1], CPU_ARG[0], CPU_ARG[1], pc_src, r_dst) : 0;
	INS_VERB ? ft_printf(V_LDI, IVA, CPU_ARG[0], CPU_ARG[1], r_dst,
		CPU_ARG[0], CPU_ARG[1], CPU_ARG[0] + CPU_ARG[1], p->pc + index) : 0;
	return (0);
}
