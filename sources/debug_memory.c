/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/25 09:39:31 by upopee           ###   ########.fr       */
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
	win != NULL ? clear_window(win) : (void)0;
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

void			debug_processes(t_cwvm *vm, t_list *curr, t_jobctrl *jobs)
{
	char		buff[LOG_BUFF_SIZE];
	t_vmverb	*verb;
	t_process	*process;
	uint32_t	ret;

	verb = &vm->ctrl.verbose;
	ret = ft_sprintf(buff, PROC_HEADER, jobs->nb_processes);
	while (curr != NULL)
	{
		process = (t_process *)curr->content;
		ft_sprintf(verb->color_buff[0], get_p_color(process->player_no));
		ft_sprintf(verb->color_buff[1], get_timercolor(process->timer));
		ret += ft_sprintf(buff + ret, PROC_INFOS, PIA);
		curr = curr->next;
	}
	clear_window(PROC_WIN);
	log_this(PWA, buff);
}

static uint32_t	print_regs(uint32_t *regs, char *buff)
{
	uint32_t	ret;
	uint8_t		reg_no;

	reg_no = 0;
	ret = 0;
	while (reg_no < REG_NUMBER)
	{
		if (reg_no == 0)
			ret += ft_sprintf(buff + ret, PREGONE, regs[reg_no]);
		else
			ret += ft_sprintf(buff + ret, (regs[reg_no] ? PREGSET :
				PREGZERO), regs[reg_no]);
		++reg_no;
	}
	ret += ft_sprintf(buff + ret, "\n");
	return (ret);
}

void			debug_registers(t_vmverb *verb, t_list *curr)
{
	char		buff[LOG_BUFF_SIZE];
	t_process	*process;
	uint32_t	ret;

	ret = ft_sprintf(buff, REG_HEADER);
	while (curr != NULL)
	{
		process = (t_process *)curr->content;
		ft_sprintf(verb->color_buff[0], get_p_color(process->player_no));
		ret += ft_sprintf(buff + ret, REG_INFOS, RWIA);
		ret += print_regs(process->registers, buff + ret);
		curr = curr->next;
	}
	clear_window(REG_WIN);
	log_this(RWA, buff);
}
