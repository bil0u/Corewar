/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op13_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:25:17 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 19:12:00 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

int		lld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	int16_t		pc_src;
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[1]);
	data = CPU_ARG[0];
	if (((CPU_OPBC >> 6) & 3) == ARG_IND)
	{
		pc_src = jump_to(p->pc, TOI16(data));
		secure_fetch(pc_src, CPU_MEM, r + r_dst - 1, REG_SIZE);
		p->carry = (r[r_dst - 1] == 0);
		INS_DEB ? log_this(IDW, D_LLDIND, IDA,
			r[r_dst - 1], TOI16(data), pc_src, r_dst, p->carry) : 0;
	}
	else
	{
		r[r_dst - 1] = data;
		p->carry = (r[r_dst - 1] == 0);
		INS_DEB ? log_this(IDW, D_LLDDIR, IDA, data, r_dst, p->carry) : 0;
	}
	INS_VERB ? ft_printf(V_LLD, IVA, r[r_dst - 1], r_dst) : 0;
	return (0);
}
