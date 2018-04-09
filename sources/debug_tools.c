/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 05:34:16 by upopee            #+#    #+#             */
/*   Updated: 2018/04/09 07:43:31 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"

/*
** -- RETURNS TRUE IF THE GIVEN VALUE IS A BUSY PROCESSES'S PC
*/

int				is_pc_val(uint32_t to_test, t_cwdata *env)
{
	uint8_t		curr_player;
	t_list		*curr_process;

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
** -- PRINT THE MSG PARAM AND RETURNS A FAILURE STATUS
*/

int				err_msg(char *msg)
{
	ft_printf(msg);
	return (FAILURE);
}
