/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/08 12:15:51 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "corewar_verbose.h"

int		is_pc_val(uint32_t to_test, t_cwdata *env)
{
	int		curr_player;
	t_list	*curr_process;

	curr_player = 0;
	while (curr_player < env->nb_players)
	{
		curr_process = (env->players + curr_player)->processes;
		while (curr_process != NULL)
		{
			if (((t_process *)(curr_process->content))->pc == to_test)
				return ((env->players + curr_player)->player_no);
			curr_process = curr_process->next;
		}
		++curr_player;
	}
	return (FALSE);
}

/*
** -- PRINT MEMORY CONTENT (IN HEX)
**    > Print the cpu->pc in red, and the filled memory cells in yellow
*/

void	print_memory(t_cwdata *env, char *win)
{
	char		buff[PRINT_BUFF_SIZE];
	uint32_t	i;
	uint32_t	ret;
	uint8_t		player_no;

	i = 0;
	ret = 0;
	win != NULL ? clear_window(win) : (void)0;
	ret += ft_sprintf(buff,
			(win != NULL ? MEM_HEADER : CW_RESTART), env->cpu.tick);
	while (i < MEM_SIZE)
	{
		if ((i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, MEM_VALUE, ((i / BPL) * BPL));
		if ((player_no = is_pc_val(i, env)) == 1)
			ret += ft_sprintf(buff + ret, PCCOLOR_P1, env->arena[i]);
		else if (player_no == 2)
			ret += ft_sprintf(buff + ret, PCCOLOR_P2, env->arena[i]);
		else if (player_no == 3)
			ret += ft_sprintf(buff + ret, PCCOLOR_P3, env->arena[i]);
		else if (player_no == 4)
			ret += ft_sprintf(buff + ret, PCCOLOR_P4, env->arena[i]);
		else if (env->arena[i])
			ret += ft_sprintf(buff + ret, MEMSET_COLOR, env->arena[i]);
		else
			ret += ft_sprintf(buff + ret, MEMZERO_COLOR, env->arena[i]);
		i++;
		if ((i & (BPL - 1)) == 0)
			ret += ft_sprintf(buff + ret, "\n");
	}
	if (win != NULL)
		ret += ft_sprintf(buff + ret, (win != NULL ? MEM_FOOTER : CW_RESTART),
		env->control.to_die, env->control.last_check, env->control.max_checks, env->control.nb_processes);
	log_this(win, 0, buff);
}

/*
** -- PRINT REGISTERS CONTENT (IN HEX)
*/

void	print_registers(t_process *p, char *win)
{
	char		buff[PRINT_BUFF_SIZE * 4];
	int			i;
	uint32_t	ret;

	ret = 0;
	win ? clear_window(win) : (void)ret;
	ret += ft_sprintf(buff, REG_HEADER, p->carry, p->timer);
	i = -1;
	while (++i < (REG_NUMBER >> 1))
		ret += ft_sprintf(buff + ret, REGN, i + 1);
	ret += ft_sprintf(buff + ret, REG_ENDL1);
	i = -1;
	while (++i < (REG_NUMBER >> 1))
	{
		ret += ft_sprintf(buff + ret, REG_SEPH);
		ret += ft_sprintf(buff + ret, p->registers[i] ? REGSET_COLOR
											: REGZERO_COLOR, p->registers[i]);
	}
	ret += ft_sprintf(buff + ret, REG_ENDL2);
	i = -1;
	while (++i < (REG_NUMBER >> 1))
		ret += ft_sprintf(buff + ret, REG_SEPL);
	ret += ft_sprintf(buff + ret, REG_ENDL1);
	i = (REG_NUMBER >> 1) - 1;
	while (++i < REG_NUMBER)
	{
		ret += ft_sprintf(buff + ret, REG_SEPH);
		ret += ft_sprintf(buff + ret, p->registers[i] ? REGSET_COLOR
											: REGZERO_COLOR, p->registers[i]);
	}
	ret += ft_sprintf(buff + ret, REG_ENDL2);
	i = (REG_NUMBER >> 1) - 1;
	while (++i < REG_NUMBER)
		ret += ft_sprintf(buff + ret, REGN, i + 1);
	ret += ft_sprintf(buff + ret, REG_ENDL1);

	log_this(win, 0, buff);
}
/*
** -- PRINT THE MSG PARAM AND RETURNS A FAILURE STATUS
*/

int		err_msg(char *msg)
{
	ft_printf(msg);
	return (FAILURE);
}
