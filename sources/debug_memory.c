/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/24 18:07:04 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "vm_debug.h"
#include "cpu_debug.h"

/*
** -- PRINT MEMORY CONTENT (IN HEX)
**    > Print the cpu->pc in red, and the filled memory cells in yellow
*/

void			debug_memory(uint8_t *arena, t_list *processes, char *win)
{
	char		buff[LOG_BUFF_SIZE];
	uint32_t	i;
	uint32_t	ret;
	uint8_t		p_no;

	i = 0;
	win != NULL ? clear_window(win) : (void)0;
	ret = (win != NULL ? ft_sprintf(buff, MEM_HEADER) : 0);
	while (i < MEM_SIZE)
	{
		if ((i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, MEM_VALUE, ((i / BPL) * BPL));
		if ((p_no = is_pc_val(i, processes)) > 0)
			ret += ft_sprintf(buff + ret, get_p_pccolor(p_no), arena[i]);
		else if (arena[i] != 0)
			ret += ft_sprintf(buff + ret, MEMSET_COLOR, arena[i]);
		else
			ret += ft_sprintf(buff + ret, MEMZERO_COLOR, arena[i]);
		if ((++i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, "\n");
	}
	log_this(win, 0, buff);
}

static char		*get_timercolor(uint16_t timer)
{
	if (timer == 0)
		return (TIMECOL_NOW);
	else if (timer < IMM_LIMIT)
		return (TIMECOL_IMM);
	else if (timer < VNEAR_LIMIT)
		return (TIMECOL_VNEAR);
	else if (timer < NEAR_LIMIT)
		return (TIMECOL_FAR);
	else
		return (TIMECOL_FAR);
}

void			debug_process(t_cwvm *vm, t_list *p, t_jobctrl *j)
{
	char		buff[LOG_BUFF_SIZE];
	t_vmverb	*v;
	t_process	*pr;
	uint32_t	r;

	clear_window(PROC_WIN);
	v = &vm->ctrl.verbose;
	r = ft_sprintf(buff, PROC_HEADER, j->nb_processes);
	while (p != NULL)
	{
		pr = (t_process *)p->content;
		ft_sprintf(v->color_buff[0], get_p_color(pr->player_no));
		ft_sprintf(v->color_buff[1], get_timercolor(pr->timer));
		r += ft_sprintf(buff + r, PROC_INFOS, PIA);
		p = p->next;
	}
	log_this(PWA, buff);
}

// void			debug_registers(t_jobctrl *j)
// {
// 	// uint8_t		reg;
//
//
//
// 	char		buff[LOG_BUFF_SIZE];
// 	t_process	*pr;
// 	uint32_t	r;
//
// 	clear_window(PROC_WIN);
// 	r = ft_sprintf(buff, REG_HEADER);
// 	while (p != NULL && p->content != NULL)
// 	{
// 		pr = (t_process *)p->content;
// 		reg = 0;
// 		while (reg < REG_NUMBER)
// 		{
// 			if (reg == 0)
// 				r += ft_sprintf(buff + r, PREGONE, pr->registers[reg]);
// 			else
// 				r += ft_sprintf(buff + r, (pr->registers[reg] ? PREGSET : \
// 					PREGZERO), pr->registers[reg]);
// 			++reg;
// 		}
// 		r += ft_sprintf(buff + r, "\n");
// 		p = p->next;
// 	}
// 	log_this(RWA, buff);
// }
