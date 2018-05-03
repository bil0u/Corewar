/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 06:28:42 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "vm_debug.h"
#include "cpu_debug.h"

/*
** -- PRINT MEMORY CELL IN HEX AND REMOVE PC OR RECENT WRITE FLAGS IF SET
*/

static void		print_pcell(uint16_t *f, uint8_t cell, char *buff, uint32_t *r)
{
	uint8_t		p_no;

	if ((*f >> CWCF_PCSHIFT) == CWCF_NONE)
	{
		p_no = get_pno((*f >> NB_CFLAGS) & 0xF);
		*r += ft_sprintf(buff + *r, get_p_color(p_no), cell);
		if (*f & CWCF_RWRITE)
		{
			*r += ft_sprintf(buff + *r, MEMWR_COLOR);
			BUNSET(*f, CWCF_RWRITE);
		}
		*r += ft_sprintf(buff + *r, MEMSET_COLOR, cell);
	}
	else
	{
		if (((*f >> NB_CFLAGS) & 0xF) == 0)
			p_no = 0;
		else
			p_no = get_pno((*f >> CWCF_PCSHIFT) & 0xF);
		*r += ft_sprintf(buff + *r, get_p_pccolor(p_no), cell);
		BUNSET(*f, CWCF_PCNO(p_no));
	}
}

/*
** -- PRINT MEMORY CONTENT (IN HEX) WITH COLORS
**    > PCs are background colored
**    > Recent writes are highlighted
**    > Empty cells are in white
*/

void			debug_memory(uint8_t *arena, uint16_t *a_flags, char *win)
{
	char		buff[LOG_BUFF_SIZE];
	uint32_t	ret;
	uint16_t	i;
	uint8_t		cell;

	i = 0;
	ret = (win != NULL ? ft_sprintf(buff, MEM_HEADER) : 0);
	while (i < MEM_SIZE)
	{
		cell = arena[i];
		if ((i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, MEM_VALUE, ((i / BPL) * BPL));
		if (a_flags[i] == CWCF_NONE)
			ret += ft_sprintf(buff + ret, MEMZERO_COLOR, cell);
		else
			print_pcell(a_flags + i, cell, buff, &ret);
		if ((++i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, "\n");
	}
	clear_window(win);
	log_this(win, 0, buff);
}

/*
** -- PRINT PROCESSES LIST AND ASSOCIATED INFORMATIONS
*/

void			debug_processes(t_cwvm *vm, t_list *curr, t_jobctrl *jobs)
{
	char		buff[LOG_BUFF_SIZE];
	t_vmverb	*verb;
	t_process	*process;
	uint32_t	ret;

	verb = &vm->ctrl.verbose;
	ret = ft_sprintf(buff, PROC_HEADER, jobs->nb_processes, vm->game.tot_lives);
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

/*
** -- PRINT PROCESSES REGISTERS
*/

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
