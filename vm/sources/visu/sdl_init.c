/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 18:31:03 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 13:16:53 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

static int	init_sdldata(t_sdl *sdlinfo)
{
	SDL_Surface	*icon;

	BKGROUND_SCREEN = NULL;
	TITLE_SCREEN = NULL;
	MAINSCREEN = NULL;
	NAVI = NULL;
	sdlinfo->save = FALSE;
	CUR_X = 0;
	CUR_Y = MEM_SIZE;
	if (SDL_Init(SDL_INIT_EVERYTHING) == FAILURE)
		return (FAILURE);
	icon = IMG_Load(CW_ICON);
	SDL_WM_SetIcon(icon, NULL);
	SDL_FreeSurface(icon);
	MAINSCREEN = SDL_SetVideoMode(WINDOW_W, WINDOW_H, BPP,
		SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	if (MAINSCREEN == NULL || ttf_init(sdlinfo) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int			init_sdl(t_sdl *sdlinfo)
{
	if (init_sdldata(sdlinfo) == FAILURE)
		return (FAILURE);
	if (start_screen(sdlinfo) == FAILURE)
		return (FAILURE);
	if (sdlinfo->save == TRUE)
	{
		sdl_clean(sdlinfo, 0, 1);
		title_screen(sdlinfo);
	}
	if (sdlinfo->save == FALSE)
		return (FAILURE);
	return (SUCCESS);
}

int			quit_sdl(t_sdl *sdlinfo)
{
	SDL_FreeSurface(sdlinfo->screen);
	TTF_CloseFont(sdlinfo->police_game);
	TTF_CloseFont(sdlinfo->police_start_screen);
	TTF_Quit();
	SDL_Quit();
	return (SUCCESS);
}
