/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mainscreen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 06:50:27 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 12:21:57 by susivagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

static int		update_gamemode2(t_sdl *sdlinfo, uint16_t *af)
{
	get_block_color(sdlinfo);
	if (af[CUR_X] == CWCF_NONE)
		MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, "  ",
			sdlinfo->grey, sdlinfo->white);
	else
		MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, "  ",
			sdlinfo->txt_color, sdlinfo->bg_color);
	if (MEM_ZONE == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int		update_gamemode1(t_sdl *sdlinfo, uint8_t *ar, uint16_t *af)
{
	set_flags(sdlinfo, ar[CUR_X], af[CUR_X]);
	if (GAMEMODE == 2)
	{
		get_txt_color(sdlinfo);
		if (*af == CWCF_NONE)
			MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, "00",
				sdlinfo->grey, sdlinfo->white);
		else
			MEM_ZONE = TTF_RenderText_Shaded(sdlinfo->police_game, DATA,
				sdlinfo->txt_color, sdlinfo->bg_color);
		if (MEM_ZONE == NULL)
			return (FAILURE);
	}
	else if ((update_gamemode2(sdlinfo, af)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int		main_screen_update(t_sdl *sdlinfo, uint8_t *ar, uint16_t *af)
{
	SDL_Rect	memzone_pos;

	PLAYER = 1;
	while (CUR_X != CUR_Y)
	{
		memzone_pos.x = ((CUR_X & 63) == 0) ? 0 : (CUR_X & 63) * PIX_X;
		memzone_pos.y = (CUR_X / 64 == 0) ? 0 : (CUR_X / 64) * PIX_Y;
		if (update_gamemode1(sdlinfo, ar, af) == FAILURE)
			return (FAILURE);
		if ((SDL_BlitSurface(MEM_ZONE, NULL, MAINSCREEN, &memzone_pos)) < 0)
			return (FAILURE);
		sdl_free(MEM_ZONE, NULL, NULL);
		BUNSET(af[CUR_X], CWCF_RWRITE);
		CUR_X++;
		if ((CUR_X == MEM_SIZE) && (CUR_Y != MEM_SIZE))
			CUR_X = 0;
	}
	return (SUCCESS);
}

static int		event_handler(t_sdl *sdlinfo, t_vmctrl *c)
{
	while (SDL_PollEvent(&(sdlinfo->event)))
	{
		SDL_Flip(MAINSCREEN);
		if (EVENT_TYPE == SDL_KEYDOWN)
		{
			if (EVENT_KEY == SDLK_RETURN)
				sdlinfo->save = 1;
			else if (EVENT_KEY == SDLK_SPACE)
				c->paused = !(c->paused);
			else if (EVENT_KEY == SDLK_RIGHT)
				c->key = '\n';
			return (SUCCESS);
		}
		else if (EVENT_TYPE == SDL_QUIT || EVENT_KEY == SDLK_ESCAPE)
		{
			sdlinfo->save = 0;
			c->stop = TRUE;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int				main_screen(t_sdl *sdlinfo, uint8_t *arena,
								uint16_t *a_flags, t_vmctrl *c)
{
	sdlinfo->save = 2;
	CUR_X = 0;
	CUR_Y = MEM_SIZE;
	if ((event_handler(sdlinfo, c)) != FAILURE)
	{
		if (main_screen_update(sdlinfo, arena, a_flags) == FAILURE)
			return (FAILURE);
		SDL_Flip(MAINSCREEN);
	}
	if (sdlinfo->save == 0)
		return (FAILURE);
	return (SUCCESS);
}
