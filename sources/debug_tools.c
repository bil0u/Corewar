/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 05:34:16 by upopee            #+#    #+#             */
/*   Updated: 2018/04/11 22:08:05 by upopee           ###   ########.fr       */
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
	t_list		*curr_process;
	t_process	*proc_data;

	curr_process = env->processes;
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
