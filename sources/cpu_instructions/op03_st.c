/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op03_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:19:20 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 19:11:21 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

int		st_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint16_t	pc_dst;
	uint8_t		r_src;

	r = p->registers;
	r_src = TOU8(CPU_ARG[0]);
	data = CPU_ARG[1];
	if (((CPU_OPBC >> 4) & 3) == ARG_IND)
	{
		pc_dst = jump_to(p->pc, TOU16(data));
		secure_store(pc_dst, CPU_MEM, r[r_src - 1], REG_SIZE);
		INS_DEB ? log_this(IDW, D_STIND, IDA,
			r[r_src - 1], r_src, TOU16(data), pc_dst) : 0;
	}
	else
	{
		r[TOU8(data) - 1] = r[r_src - 1];
		if (INS_DEB)
			log_this(IDW, D_STREG, IDA, r[r_src - 1], r_src, TOU8(data));
	}
	INS_VERB ? ft_printf(V_ST, IVA, r_src, r[r_src - 1]) : 0;
	return (0);
}
