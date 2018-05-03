/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op02_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:19:02 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 06:30:16 by upopee           ###   ########.fr       */
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

int		ld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	int16_t		ind;
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[1]);
	if (((CPU_OPBC >> 6) & 3) == ARG_IND)
	{
		ind = TOI16(CPU_ARG[0]) % IDX_MOD;
		decode_arg(CPU_MEM, p, ARG_IND, CPU_ARG);
		r[r_dst - 1] = CPU_ARG[0];
		INS_DEB ? log_this(IDW, D_LDIND, IDA, r[r_dst - 1], ind,
			jump_to(p->pc, ind), r_dst, p->carry) : 0;
	}
	else
	{
		r[r_dst - 1] = CPU_ARG[0];
		INS_DEB ? log_this(IDW, D_LDDIR, IDA, CPU_ARG[0], r_dst, p->carry) : 0;
	}
	p->carry = (r[r_dst - 1] == 0);
	INS_VERB ? ft_printf(V_LD, IVA, r[r_dst - 1], r_dst) : 0;
	return (0);
}
