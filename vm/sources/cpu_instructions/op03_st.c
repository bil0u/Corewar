/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op03_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:19:20 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 06:30:18 by upopee           ###   ########.fr       */
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

int		st_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		r_src;

	r = p->registers;
	r_src = TOU8(CPU_ARG[0]);
	data = CPU_ARG[1];
	if (((CPU_OPBC >> 4) & 3) == ARG_IND)
	{
		cpu->pc_copy = jump_to(p->pc, TOI16(data) % IDX_MOD);
		secure_store(cpu, p->player_no, r[r_src - 1], REG_SIZE);
		INS_DEB ? log_this(IDW, D_STIND, IDA,
			r[r_src - 1], r_src, TOI16(data) % IDX_MOD, cpu->pc_copy) : 0;
	}
	else
	{
		r[TOU8(data) - 1] = r[r_src - 1];
		if (INS_DEB)
			log_this(IDW, D_STREG, IDA, r[r_src - 1], r_src, TOU8(data));
	}
	INS_VERB ? ft_printf(V_ST, IVA, r_src, TOI16(data)) : 0;
	return (0);
}
