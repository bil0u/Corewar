/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op14_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:25:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/28 22:12:07 by upopee           ###   ########.fr       */
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
	int32_t		index;
	uint16_t	pc_src;
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[2]);
	NEED_ZBUG && ((CPU_OPBC >> 6) & 3) == ARG_IND ? CPU_ARG[0] %= IDX_MOD : 0;
	NEED_ZBUG && ((CPU_OPBC >> 4) & 3) == ARG_IND ? CPU_ARG[1] %= IDX_MOD : 0;
	decode_arg(CPU_MEM, p, (CPU_OPBC >> 6) & 3, CPU_ARG);
	decode_arg(CPU_MEM, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1);
	index = TOI32(CPU_ARG[0]) + TOI32(CPU_ARG[1]);
	pc_src = jump_to(p->pc, TOI16(NEED_ZBUG ? index % IDX_MOD : index));
	secure_fetch(CPU_MEM, pc_src, r + r_dst - 1, REG_SIZE);
	p->carry = (r[r_dst - 1] == 0);
	INS_DEB ? log_this(IDW, D_LLDI, IDA,
		r[r_dst - 1], CPU_ARG[0], CPU_ARG[1], pc_src, r_dst, p->carry) : 0;
	INS_VERB ? ft_printf(V_LLDI, IVA, CPU_ARG[0], CPU_ARG[1], r_dst, CPU_ARG[0],
		CPU_ARG[1], CPU_ARG[0] + CPU_ARG[1], p->pc + index) : 0;
	return (0);
}
