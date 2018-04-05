/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 19:06:50 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "corewar_verbose.h"

int		is_pc_val(uint32_t to_test, t_cwdata *env)
{
	int		curr_player;
	t_list	*processes;

	curr_player = 0;
	while (curr_player < env->nb_players)
	{
		processes = (env->players + curr_player)->processes;
		while (processes != NULL)
		{
			if (((t_process *)(processes->content))->pc == to_test)
				return ((env->players + curr_player)->player_no);
			processes = processes->next;
		}
		++curr_player;
	}
	return (FALSE);
}

/*
** -- PRINT MEMORY CONTENT (IN HEX)
**    > Print the cpu->pc in red, and the filled memory cells in yellow
*/

// void	print_memory(t_cwdata *env, char clean)
// {
// 	char		buff[600];
// 	uint32_t	i;
// 	uint32_t	ret;
// 	uint8_t		player_no;
//
// 	i = 0;
// 	ret = 0;
// 	clean ? clear_window("mem") : (void)ret;
// 	ft_bzero(buff, sizeof(*buff));
// 	while (i < MEM_SIZE)
// 	{
// 		if ((i & (BPL - 1)) == 0)
// 			ret += ft_sprintf(buff + ret, MEM_VALUE, ((i / BPL) * BPL));
// 		if ((player_no = is_pc_val(i, env)) == 1)
// 			ret += ft_sprintf(buff + ret, PCCOLOR_P1, env->arena[i]);
// 		else if (player_no == 2)
// 			ret += ft_sprintf(buff + ret, PCCOLOR_P2, env->arena[i]);
// 		else if (player_no == 3)
// 			ret += ft_sprintf(buff + ret, PCCOLOR_P3, env->arena[i]);
// 		else if (player_no == 4)
// 			ret += ft_sprintf(buff + ret, PCCOLOR_P4, env->arena[i]);
// 		else if (env->arena[i])
// 			ret += ft_sprintf(buff + ret, MEMSET_COLOR, env->arena[i]);
// 		else
// 			ret += ft_sprintf(buff + ret, MEMZERO_COLOR, env->arena[i]);
// 		i++;
// 		if ((i & (BPL - 1)) == 0)
// 			ret += ft_sprintf(buff + ret, "\n");
// 	}
// 	log_this("mem", 0, buff);
// }

void	print_memory(t_vcpu *cpu, char clean)
{
	char		buff[4096];
	uint32_t	i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	if (clean)
		clear_window("mem");
	while (i < MEM_SIZE)
	{
		if (i == cpu->pc[0])
			ret += ft_sprintf(buff + ret, PCCOLOR_P1, cpu->memory[i]);
		else if (cpu->memory[i])
			ret += ft_sprintf(buff + ret, MEMSET_COLOR, cpu->memory[i]);
		else
			ret += ft_sprintf(buff + ret, MEMZERO_COLOR, cpu->memory[i]);
		++i;
	}
	buff[ret] = '\n';
	buff[ret + 1] = '\0';
	log_this("mem", 0, buff);
}

/*
** -- PRINT REGISTERS CONTENT (IN HEX)
*/

void	print_registers(t_vcpu *cpu, char clean)
{
	char		buff[4096];
	uint8_t		i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	clean ? clear_window("reg") : (void)ret;
	while (i < REG_NUMBER)
	{
		if (cpu->registers[i])
			ret += ft_sprintf(buff + ret, "{yellow}%8.8x{eoc}", cpu->registers[i]);
		else
			ret += ft_sprintf(buff + ret, "%8.8x", cpu->registers[i]);
		i++;
		if (i != REG_NUMBER)
			ret += ft_sprintf(buff + ret, "{red}|{eoc}");
	}
	buff[ret] = '\n';
	buff[ret + 1] = '\0';
	log_this("reg", 0, buff);
}

/*
** -- PRINT THE MSG PARAM AND RETURNS A FAILURE STATUS
*/

int		err_msg(char *msg)
{
	ft_printf(msg);
	return (FAILURE);
}
