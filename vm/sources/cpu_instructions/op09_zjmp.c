/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op09_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:21:48 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 06:30:33 by upopee           ###   ########.fr       */
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

int		zjmp_instr(t_vcpu *cpu, t_process *p)
{
	uint16_t	pc_dst;
	int16_t		index;

	secure_fetch(CPU_MEM, jump_to(p->pc, OPBC_SIZE), CPU_ARG, ARG_INDSZ);
	ARG_DEB ? log_this(ADW, D_ARG_DIR, 1, CPU_ARG[0]) : 0;
	index = TOI16(CPU_ARG[0]);
	if (p->carry == 1)
	{
		pc_dst = jump_to(p->pc, index % IDX_MOD);
		ARG_DEB ? debug_pcmove(p->pc, cpu->memory, cpu->b_read + ARG_INDSZ) : 0;
		INS_DEB ? log_this(IDW, D_ZJMPOK, IDA, index, pc_dst) : 0;
		INS_VERB ? ft_printf(V_ZJMPOK, IVA, index) : 0;
		p->pc = pc_dst;
		return (-OPBC_SIZE);
	}
	else
	{
		INS_DEB ? log_this(IDW, D_ZJMPKO, IDA, index) : 0;
		INS_VERB ? ft_printf(V_ZJMPKO, IVA, index) : 0;
		return (ARG_INDSZ);
	}
}
