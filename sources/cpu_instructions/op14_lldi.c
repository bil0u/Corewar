/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op14_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:25:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 19:12:04 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

int		lldi_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint16_t	pc_src;
	int16_t		index;
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[2]);
	decode_arg(cpu->memory, p, (CPU_OPBC >> 6) & 3, CPU_ARG);
	decode_arg(cpu->memory, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1);
	index = TOI16(TOI32(CPU_ARG[0]) + TOI32(CPU_ARG[1]));
	pc_src = jump_to(p->pc, index);
	secure_fetch(pc_src, CPU_MEM, r + r_dst - 1, REG_SIZE);
	p->carry = (r[r_dst - 1] == 0);
	INS_DEB ? log_this(IDW, D_LLDI, IDA,
		r[r_dst - 1], CPU_ARG[0], CPU_ARG[1], pc_src, r_dst, p->carry) : 0;
	INS_VERB ? ft_printf(V_LLDI, IVA, CPU_ARG[0], CPU_ARG[1], r_dst,
		CPU_ARG[0], CPU_ARG[1], CPU_ARG[0] + CPU_ARG[1], pc_src) : 0;
	return (0);
}
