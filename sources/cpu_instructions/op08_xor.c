/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op08_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:21:20 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 19:11:43 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

int		xor_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		r_dst;

	r = p->registers;
	r_dst = TOU8(CPU_ARG[2]);
	decode_arg(cpu->memory, p, (CPU_OPBC >> 6) & 3, CPU_ARG);
	decode_arg(cpu->memory, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1);
	r[r_dst - 1] = CPU_ARG[0] ^ CPU_ARG[1];
	p->carry = (r[r_dst - 1] == 0);
	if (INS_DEB)
		log_this(IDW, D_XOR, IDA,
			CPU_ARG[0], CPU_ARG[1], r[r_dst - 1], r_dst, p->carry);
	if (INS_VERB)
		ft_printf(V_XOR, IVA, CPU_ARG[0], CPU_ARG[1], r_dst);
	return (0);
}
