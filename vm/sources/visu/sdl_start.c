/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 18:36:55 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 14:09:56 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

static int	start_event(t_sdl *sdlinfo)
{
	while (SDL_PollEvent(&(sdlinfo->event)))
	{
		SDL_Flip(MAINSCREEN);
		if (EVENT_TYPE == SDL_KEYDOWN)
		{
			if (EVENT_KEY == SDLK_SPACE)
			{
				sdlinfo->save = TRUE;
				return (SUCCESS);
			}
		}
		else if (EVENT_TYPE == SDL_QUIT || EVENT_KEY == SDLK_ESCAPE)
		{
			sdlinfo->save = FALSE;
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

static int	start_screen_set(t_sdl *sdlinfo)
{
	BKGROUND_SCREEN = IMG_Load(CW_SBG);
	SDL_BlitSurface(BKGROUND_SCREEN, NULL, MAINSCREEN, &BKGROUND_POS);
	TITLE_SCREEN = IMG_Load(CW_LOGO);
	SDL_BlitSurface(TITLE_SCREEN, NULL, MAINSCREEN, &TITLES_POS);
	MEM_ZONE = TTF_RenderText_Blended(sdlinfo->police_start_screen,
		"Press Space", sdlinfo->pc_red);
	SDL_BlitSurface(MEM_ZONE, NULL, MAINSCREEN, &PRESS_POS);
	if ((BKGROUND_SCREEN == NULL) || (TITLE_SCREEN == NULL) ||
		(MEM_ZONE == NULL))
		return (FAILURE);
	return (SUCCESS);
}

int			start_screen(t_sdl *sdlinfo)
{
	BKGROUND_POS.x = 0;
	BKGROUND_POS.y = 0;
	TITLES_POS.x = 73;
	TITLES_POS.y = 550;
	PRESS_POS.x = 293;
	PRESS_POS.y = 720;
	CREDIT_POS.x = 5;
	CREDIT_POS.y = 780;
	while ((start_event(sdlinfo)) == FAILURE)
	{
		SDL_WM_SetCaption("-- COREWAR --", NULL);
		if (!BKGROUND_SCREEN && (start_screen_set(sdlinfo) == FAILURE))
		{
			ft_printf("Cannot init the start screen\n");
			return (FAILURE);
		}
		SDL_Flip(MAINSCREEN);
	}
	return (SUCCESS);
}
