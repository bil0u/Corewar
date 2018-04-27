/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 05:34:16 by upopee            #+#    #+#             */
/*   Updated: 2018/04/27 17:07:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "vm_debug.h"

/*
** -- RETURNS PLAYER_NO FROM GIVEN ARENA FLAGS
*/

uint8_t			get_pno(uint8_t a_flags)
{
	uint8_t		player_no;

	a_flags >>= 2;
	player_no = 0;
	while (!((a_flags >> player_no) & 1))
		++player_no;
	return (player_no + 1);
}

/*
** -- RETURNS COLORS FOR A GIVEN PLAYER NO
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
