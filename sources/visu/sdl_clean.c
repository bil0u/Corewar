/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 06:36:22 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 15:17:26 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

int		sdl_clean(t_sdl *sdlinfo, int resize, int surface_free)
{
	if (resize == 1)
		SDL_FreeSurface(MAINSCREEN);
	if (resize == 1 && (MAINSCREEN = SDL_SetVideoMode(WINDOW_BIGW,
		WINDOW_BIGH, BPP, SDL_HWSURFACE)) == NULL
		&& ft_printf("Cannot init main screen : '%s'\n", SDL_GetError()))
		return (FAILURE);
	SDL_FillRect(MAINSCREEN, NULL,
		SDL_MapRGB(MAINSCREEN->format, sdlinfo->bg_grey.r,
			sdlinfo->bg_grey.g, sdlinfo->bg_grey.b));
	SDL_Flip(MAINSCREEN);
	if (surface_free == 1)
		sdl_free(BKGROUND_SCREEN, TITLE_SCREEN, MEM_ZONE);
	return (SUCCESS);
}

int		sdl_free(SDL_Surface *tofree1, SDL_Surface *tofree2,
		SDL_Surface *tofree3)
{
	if (tofree1 != NULL)
		SDL_FreeSurface(tofree1);
	if (tofree2 != NULL)
		SDL_FreeSurface(tofree2);
	if (tofree3 != NULL)
		SDL_FreeSurface(tofree3);
	tofree1 = NULL;
	tofree2 = NULL;
	tofree3 = NULL;
	return (SUCCESS);
}
