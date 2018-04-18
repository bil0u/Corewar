/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 05:34:16 by upopee            #+#    #+#             */
/*   Updated: 2018/04/18 23:32:21 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vcpu_types.h"
#include "corewar_types.h"
#include "memory_verbose.h"

/*
** -- RETURNS TRUE IF THE GIVEN VALUE IS A BUSY PROCESSES'S PC
*/

int				is_pc_val(uint32_t to_test, t_list *curr_process)
{
	t_process	*proc_data;

	while (curr_process != NULL)
	{
		proc_data = (t_process *)curr_process->content;
		if (proc_data->pc == to_test)
			return (proc_data->player_no);
		curr_process = curr_process->next;
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

/*
** -- RETURNS COLOR FOR A GIVEN PLAYER NO
*/

char			*get_p_color(uint8_t player_no)
{
	if (player_no == 1)
		return (COL_P1);
	else if (player_no == 2)
		return (COL_P2);
	else if (player_no == 3)
		return (COL_P3);
	else if (player_no == 4)
		return (COL_P4);
	else
		return (COL_P0);
}

char			*get_p_bgcolor(uint8_t player_no)
{
	if (player_no == 1)
		return (BCOL_P1);
	else if (player_no == 2)
		return (BCOL_P2);
	else if (player_no == 3)
		return (BCOL_P3);
	else if (player_no == 4)
		return (BCOL_P4);
	else
		return (BCOL_P0);
}

char			*get_p_pccolor(uint8_t player_no)
{
	if (player_no == 1)
		return (PCC_P1);
	else if (player_no == 2)
		return (PCC_P2);
	else if (player_no == 3)
		return (PCC_P3);
	else if (player_no == 4)
		return (PCC_P4);
	else
		return (PCC_P0);
}
