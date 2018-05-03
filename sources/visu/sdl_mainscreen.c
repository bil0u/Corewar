/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mainscreen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 06:50:27 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 07:14:23 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

static int		update_gamemode2(t_sdl *sdlinfo)
{
	get_block_color(sdlinfo);
	if (F_WRITE == 1)
		MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, "  ",
			sdlinfo->bg_color, sdlinfo->black);
	else if (PLAYER > 0)
		MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, "  ",
			sdlinfo->txt_color, sdlinfo->bg_color);
	else
		MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, "  ",
			sdlinfo->txt_color, sdlinfo->grey);
	if (MEM_ZONE == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int		update_gamemode1(t_sdl *sdlinfo)
{
	F_WRITE = 0;
	FNONE = 0;
	FPC = 0;
	if (GAMEMODE == 2)
	{
		get_txt_color(sdlinfo);
		if (FNONE == 0)
			MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, "01",
				sdlinfo->txt_color, sdlinfo->bg_color);
		else
			MEM_ZONE = TTF_RenderText_Solid(sdlinfo->police_game, "00",
				sdlinfo->grey);
		if (MEM_ZONE == NULL)
			return (FAILURE);
	}
	else if ((update_gamemode2(sdlinfo)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int				main_screen(t_sdl *sdlinfo)
{
	sdlinfo->save = 2;
	if ((event_handler(sdlinfo)) != 0)
	{
		if (main_screen_update(sdlinfo) == FAILURE)
			return (FAILURE);
		SDL_Flip(MAINSCREEN);
	}
	if (sdlinfo->save == 0)
		return (FAILURE);
	return (SUCCESS);
}

int				main_screen_update(t_sdl *sdlinfo)
{
	SDL_Rect	memzone_pos;

	PLAYER = 1;
	while (CUR_X != CUR_Y)
	{
		memzone_pos.x = ((CUR_X & 63) == 0) ? 0 : (CUR_X & 63) * PIX_X;
		memzone_pos.y = (CUR_X / 64 == 0) ? 0 : (CUR_X / 64) * PIX_Y;
		if (update_gamemode1(sdlinfo) == FAILURE)
			return (FAILURE);
		if ((SDL_BlitSurface(MEM_ZONE, NULL, MAINSCREEN, &memzone_pos)) < 0)
			return (FAILURE);
		SDL_FreeSurface(MEM_ZONE);
		CUR_X++;
		if ((CUR_X == MEM_SIZE) && (CUR_Y != MEM_SIZE))
			CUR_X = 0;
	}
	return (SUCCESS);
}
