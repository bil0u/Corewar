/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op16_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:26:31 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 19:12:10 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

int		aff_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	uint8_t		r_src;
	char		to_print;

	r_src = TOU8(CPU_ARG[0]);
	to_print = TOU8(p->registers[r_src - 1]);
	if (pl->aff_bytes == 0xFF || (to_print == '\0' && pl->aff_bytes > 0))
	{
		write(1, pl->aff_buff, pl->aff_bytes);
		ft_bzero(pl->aff_buff, pl->aff_bytes);
		pl->aff_bytes = 0;
	}
	if (to_print != '\0')
	{
		pl->aff_buff[pl->aff_bytes] = to_print;
		++pl->aff_bytes;
	}
	INS_DEB ? log_this(IDW, D_AFF, IDA, to_print, r_src) : 0;
	cpu->ctrl->flags & CWF_AFFON ? ft_printf(V_AFF, to_print) : 0;
	return (0);
}
