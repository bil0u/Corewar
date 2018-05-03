/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_title.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:45:46 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 14:09:34 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

static int	title_screen_set_sup(t_sdl *sdlinfo)
{
	if ((MEM_ZONE = TTF_RenderText_Blended(sdlinfo->police_start_screen,
		"BLOCK MODE", sdlinfo->pc_red)) == NULL)
		return (FAILURE);
	SDL_BlitSurface(MEM_ZONE, NULL, MAINSCREEN, &PRESS_POS);
	sdl_free(MEM_ZONE, NULL, NULL);
	CREDIT_POS.x = 293;
	CREDIT_POS.y = 420;
	if ((MEM_ZONE = TTF_RenderText_Blended(sdlinfo->police_start_screen,
		"TEXT MODE", sdlinfo->pc_red)) == NULL)
		return (FAILURE);
	SDL_BlitSurface(MEM_ZONE, NULL, MAINSCREEN, &CREDIT_POS);
	sdl_free(MEM_ZONE, NULL, NULL);
	CREDIT_POS.x = 360;
	CREDIT_POS.y = 520;
	if ((MEM_ZONE = TTF_RenderText_Blended(sdlinfo->police_start_screen,
		"EXIT", sdlinfo->pc_red)) == NULL)
		return (FAILURE);
	SDL_BlitSurface(MEM_ZONE, NULL, MAINSCREEN, &CREDIT_POS);
	sdl_free(MEM_ZONE, NULL, NULL);
	return (SUCCESS);
}

static int	title_screen_set(t_sdl *sdlinfo)
{
	BKGROUND_SCREEN = IMG_Load(CW_TBG);
	SDL_BlitSurface(BKGROUND_SCREEN, NULL, MAINSCREEN, &BKGROUND_POS);
	sdl_free(BKGROUND_SCREEN, NULL, NULL);
	TITLE_SCREEN = IMG_Load(CW_LOGO);
	SDL_BlitSurface(TITLE_SCREEN, NULL, MAINSCREEN, &TITLES_POS);
	sdl_free(TITLE_SCREEN, NULL, NULL);
	if (title_screen_set_sup(sdlinfo) == FAILURE)
		return (FAILURE);
	CREDIT_POS.x = 260;
	CREDIT_POS.y = 750;
	MEM_ZONE = TTF_RenderText_Blended(sdlinfo->police_game,
		"Glictevo, Upopee, Jrobin, Susivagn", sdlinfo->pc_red);
	SDL_BlitSurface(MEM_ZONE, NULL, MAINSCREEN, &CREDIT_POS);
	if ((BKGROUND_SCREEN == NULL) || (TITLE_SCREEN == NULL) ||
		(MEM_ZONE == NULL))
		return (FAILURE);
	return (SUCCESS);
}

static void	navigation_key_handler(t_sdl *sdlinfo)
{
	if (EVENT_KEY == SDLK_DOWN)
	{
		if (NAVI_POS.y != 495)
			NAVI_POS.y = NAVI_POS.y + 100;
		else
			NAVI_POS.y = 295;
	}
	else if (EVENT_KEY == SDLK_UP)
	{
		if (NAVI_POS.y != 295)
			NAVI_POS.y = NAVI_POS.y - 100;
		else
			NAVI_POS.y = 495;
	}
}

static int	title_event_handler(t_sdl *sdlinfo)
{
	while (SDL_PollEvent(&(sdlinfo->event)))
	{
		SDL_Flip(MAINSCREEN);
		if (EVENT_TYPE == SDL_KEYDOWN)
		{
			if (EVENT_KEY == SDLK_DOWN || EVENT_KEY == SDLK_UP)
				navigation_key_handler(sdlinfo);
			if (EVENT_KEY == SDLK_RETURN)
			{
				if (NAVI_POS.y == 495 && (sdlinfo->save = 0) == 0)
					return (SUCCESS);
				GAMEMODE = (NAVI_POS.y == 295) ? 1 : 2;
				sdlinfo->save = TRUE;
				return (SUCCESS);
			}
		}
		else if ((EVENT_TYPE == SDL_QUIT || EVENT_KEY == SDLK_ESCAPE)
		&& (sdlinfo->save = 0) == 0)
			return (SUCCESS);
	}
	return (FAILURE);
}

int			title_screen(t_sdl *sdlinfo)
{
	TITLES_POS.y = 100;
	PRESS_POS.x = 293;
	PRESS_POS.y = 320;
	NAVI_POS.x = 268;
	NAVI_POS.y = 295;
	while (((title_event_handler(sdlinfo)) == FAILURE))
	{
		if ((title_screen_set(sdlinfo) == FAILURE))
			return (FAILURE);
		if (!NAVI)
			NAVI = IMG_Load(CW_SELECT);
		SDL_BlitSurface(NAVI, NULL, MAINSCREEN, &NAVI_POS);
		SDL_Flip(MAINSCREEN);
	}
	sdl_free(NAVI, NULL, NULL);
	if (sdlinfo->save == TRUE)
		sdl_clean(sdlinfo, 1, 0);
	return (SUCCESS);
}
