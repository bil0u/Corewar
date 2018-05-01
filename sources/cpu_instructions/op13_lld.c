/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op13_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:25:17 by upopee            #+#    #+#             */
/*   Updated: 2018/05/01 20:39:18 by upopee           ###   ########.fr       */
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
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[1]);
	if (((CPU_OPBC >> 6) & 3) == ARG_IND)
	{
		data = CPU_ARG[0];
		decode_arg(CPU_MEM, p, ARG_IND, CPU_ARG);
		r[r_dst - 1] = CPU_ARG[0];
		NEED_ZBUG ? r[r_dst - 1] >>= 16 : 0;
		INS_DEB ? log_this(IDW, D_LLDIND, IDA, r[r_dst - 1], TOI16(data),
			p->pc + TOI16(data), r_dst, p->carry) : 0;
	}
	else
	{
		r[r_dst - 1] = CPU_ARG[0];
		INS_DEB ? log_this(IDW, D_LLDDIR, IDA, CPU_ARG[0], r_dst, p->carry) : 0;
	}
	p->carry = (r[r_dst - 1] == 0);
	INS_VERB ? ft_printf(V_LLD, IVA, r[r_dst - 1], r_dst) : 0;
	return (0);
}
