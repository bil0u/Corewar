/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 14:17:16 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "corewar_verbose.h"
#include "corewar.h"

/*
** -- PRINTS THE GIVEN MEMORY CELL IN THE RIGHT COLOR
*/

uint32_t		print_cell(char *buff, uint8_t mem_cell, uint8_t player_no)
{
	if (player_no == 1)
		return (ft_sprintf(buff, PCC_P1, mem_cell));
	else if (player_no == 2)
		return (ft_sprintf(buff, PCC_P2, mem_cell));
	else if (player_no == 3)
		return (ft_sprintf(buff, PCC_P3, mem_cell));
	else if (player_no == 4)
		return (ft_sprintf(buff, PCC_P4, mem_cell));
	else if (mem_cell != 0)
		return (ft_sprintf(buff, MEMSET_COLOR, mem_cell));
	else
		return (ft_sprintf(buff, MEMZERO_COLOR, mem_cell));
}

/*
** -- PRINT MEMORY CONTENT (IN HEX)
**    > Print the cpu->pc in red, and the filled memory cells in yellow
*/

void			print_memory(uint8_t *arena, t_list *processes, char *win)
{
	char		buff[PRINT_BUFF_SIZE];
	uint32_t	i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	win != NULL ? clear_window(win) : (void)0;
	win != NULL ? ret += ft_sprintf(buff, MEM_HEADER) : (void)0;
	while (i < MEM_SIZE)
	{
		if ((i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, MEM_VALUE, ((i / BPL) * BPL));
		ret += print_cell(buff + ret, arena[i], is_pc_val(i, processes));
		i++;
		if ((i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, "\n");
	}
	log_this(win, 0, buff);
}

/*
** -- PRINTS THE N ARGS FROM GIVEN START
**    > mod = 1 : Prints the reg numbers line
**    > mod = 2 : Prints the separator line
**    > mod = 4 : Prints the registers content spaced by separators
*/

static uint32_t	print_nregs(char *dst, uint32_t *r, uint8_t s, uint8_t mod)
{
	uint8_t		i;
	uint32_t	ret;

	ret = 0;
	ret += ft_sprintf(dst + ret, mod & 3 ? REG_BEGL1 : REG_BEGL2);
	i = s + (REG_NUMBER >> 1);
	if (mod == (1 << 0))
		while (s++ < i)
			ret += ft_sprintf(dst + ret, REGN, s);
	else if (mod == (1 << 1))
		while (s++ < i)
			ret += ft_sprintf(dst + ret, SEPL);
	else if (mod == (1 << 2))
		while (s++ < i)
		{
			ret += ft_sprintf(dst + ret, r[s - 1] ?
								REGSET_COLOR : REGZERO_COLOR, r[s - 1]);
			ret += ft_sprintf(dst + ret, SEPH);
		}
	return (ret);
}

/*
** -- PRINT REGISTERS HEADER AND CONTENT (IN HEX)
*/

void			print_registers(t_player *pl, t_process *pr, char *win)
{
	char		buff[PRINT_BUFF_SIZE * 4];
	uint32_t	ret;

	win ? clear_window(win) : (void)ret;
	if (pr == NULL)
	{
		log_this(win, 0, REG_HEADER, 0, 0, 0, NULL, 0);
		return ;
	}
	ret = 0;
	ret += ft_sprintf(buff, REG_HEADER, pl->player_no, pr->pid, pr->carry,
							pr->next_op ? pr->next_op->name : NULL, pr->timer);
	ret += print_nregs(buff + ret, pr->registers, 0, (1 << 0));
	ret += print_nregs(buff + ret, pr->registers, 0, (1 << 2));
	ret += print_nregs(buff + ret, pr->registers, 0, (1 << 1));
	ret += print_nregs(buff + ret, pr->registers, (REG_NUMBER >> 1), (1 << 2));
	ret += print_nregs(buff + ret, pr->registers, (REG_NUMBER >> 1), (1 << 0));
	log_this(win, 0, buff);
}
