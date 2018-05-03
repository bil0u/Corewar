/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 18:31:03 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 07:11:24 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

static int	init_sdldata(t_sdl *sdlinfo)
{
	BKGROUND_SCREEN = NULL;
	TITLE_SCREEN = NULL;
	MAINSCREEN = NULL;
	NAVI = NULL;
	sdlinfo->save = 0;
	CUR_X = 0;
	CUR_Y = MEM_SIZE;
	if (SDL_Init(SDL_INIT_EVERYTHING) == FAILURE)
		return (FAILURE);
	MAINSCREEN = SDL_SetVideoMode(WINDOW_W, WINDOW_H, BPP,
		SDL_HWSURFACE | SDL_RESIZABLE);
	if (MAINSCREEN == NULL)
		return (FAILURE);
	if (ttf_init(sdlinfo) == FAILURE)
		return (FAILURE);
	return (1);
}

int			init_sdl(t_sdl *sdlinfo)
{
	if (init_sdldata(sdlinfo) == FAILURE)
		return (FAILURE);
	if (start_screen(sdlinfo) == FAILURE)
		return (FAILURE);
	if (sdlinfo->save == 1 && sdl_clean(sdlinfo, 0, 1))
		title_screen(sdlinfo);
	if (sdlinfo->save == 0)
		return (FAILURE);
	return (SUCCESS);
}

int			quit_sdl(t_sdl *sdlinfo)
{
	SDL_FreeSurface(sdlinfo->screen);
	SDL_Quit();
	TTF_CloseFont(sdlinfo->police_game);
	TTF_CloseFont(sdlinfo->police_start_screen);
	TTF_Quit();
	return (SUCCESS);
}
