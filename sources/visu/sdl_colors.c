/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 18:34:10 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 07:04:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

// int		set_flags(t_sdl *sdlinfo)
// {
// 	FPC = 0;
// 	F_WRITE = 0;
// 	FNONE = 0;
// 	PLAYER = 0; a GET//
// 	if (a_flags[CUR_X] == CWCF_NONE)
// 	{
// 		FNONE = 1;
// 		return (1);
// 	}
// 	DATA = ft_itoa_base(arena[CUR_X], "0123456789ABCDEF");
// 	FPC = (a_flags[CUR_X] == CWCF_PCNO(PLAYER)) ? 1 : 0;
// 	F_WRITE = (a_flags[CUR_X] == CWCF_RWRITE) ? 1 : 0;
// 	PLAYER = (a_flags[CUR_START] == CWCF_PNO(1)) ? 1 : 0;
// 	PLAYER = (a_flags[CUR_START] == CWCF_PNO(2)) ? 1 : 0;
// 	PLAYER = (a_flags[CUR_START] == CWCF_PNO(3)) ? 1 : 0;
// 	PLAYER = (a_flags[CUR_START] == CWCF_PNO(4)) ? 1 : 0;
// 	return (1);
// }

void	get_block_color(t_sdl *sdlinfo)
{
	if (FPC == 0 && F_WRITE == 1)
	{
		if (PLAYER == 1)
			sdlinfo->bg_color = sdlinfo->red;
		else if (PLAYER == 2)
			sdlinfo->bg_color = sdlinfo->blue;
		else if (PLAYER == 3)
			sdlinfo->bg_color = sdlinfo->green;
		else if (PLAYER == 4)
			sdlinfo->bg_color = sdlinfo->yellow;
	}
	else
	{
		if (PLAYER == 1)
			sdlinfo->bg_color = sdlinfo->pc_red;
		else if (PLAYER == 2)
			sdlinfo->bg_color = sdlinfo->pc_blue;
		else if (PLAYER == 3)
			sdlinfo->bg_color = sdlinfo->pc_green;
		else if (PLAYER == 4)
			sdlinfo->bg_color = sdlinfo->pc_yellow;
	}
}

void	get_txt_color(t_sdl *sdlinfo)
{
	if (F_WRITE == 1)
		get_wrt_txt_color(sdlinfo);
	else if (FPC == 0)
	{
		sdlinfo->bg_color = sdlinfo->black;
		if (PLAYER == 1)
			sdlinfo->txt_color = sdlinfo->red;
		else if (PLAYER == 2)
			sdlinfo->txt_color = sdlinfo->blue;
		else if (PLAYER == 3)
			sdlinfo->txt_color = sdlinfo->green;
		else if (PLAYER == 4)
			sdlinfo->txt_color = sdlinfo->yellow;
	}
	else
	{
		sdlinfo->txt_color = sdlinfo->black;
		if (PLAYER == 1)
			sdlinfo->bg_color = sdlinfo->red;
		else if (PLAYER == 2)
			sdlinfo->bg_color = sdlinfo->blue;
		else if (PLAYER == 3)
			sdlinfo->bg_color = sdlinfo->green;
		else if (PLAYER == 4)
			sdlinfo->bg_color = sdlinfo->yellow;
	}
}

void	get_wrt_txt_color(t_sdl *sdlinfo)
{
	sdlinfo->bg_color = sdlinfo->black;
	if (PLAYER == 1)
		sdlinfo->txt_color = sdlinfo->pc_red;
	else if (PLAYER == 2)
		sdlinfo->txt_color = sdlinfo->pc_blue;
	else if (PLAYER == 3)
		sdlinfo->txt_color = sdlinfo->pc_green;
	else if (PLAYER == 4)
		sdlinfo->txt_color = sdlinfo->pc_yellow;
}
