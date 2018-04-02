/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:04:17 by upopee            #+#    #+#             */
/*   Updated: 2018/04/02 21:05:32 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "sdl_test.h"

void	init_window(SDL_Surface **screen)
{
	SDL_Surface	*icon;
	uint32_t	win_flags;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != -1)
	{
		icon = IMG_Load(LOGO_PATH);
		SDL_WM_SetIcon(icon, NULL);
		SDL_FreeSurface(icon);
		win_flags = SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF;
		*screen = SDL_SetVideoMode(WINSZ_X, WINSZ_Y, 32, win_flags);
		if (*screen != NULL)
			SDL_WM_SetCaption(WIN_NAME, NULL);
		else
			printf("Impossible d'initialiser la fenetre: %s\n", SDL_GetError());
	}
	else
		printf("Impossible d'initialiser SDL: %s\n", SDL_GetError());
}

void 	init_images(SDL_Surface **images)
{
	images[0] = IMG_Load(BG_PATH);
	images[1] = IMG_Load(LOGO_PATH);
	images[2] = NULL;
}

void	put_images(SDL_Surface *screen, SDL_Surface **images)
{
	int			i;
	SDL_Rect	dst;

	i = -1;
	while (images[++i] != NULL)
	{
		dst.w = images[i]->w;
		dst.h = images[i]->h;
		dst.x = (WINSZ_X >> 1) - (dst.w >> 1);
		dst.y = (WINSZ_Y >> 1) - (dst.h >> 1);
		SDL_BlitSurface(images[i], NULL, screen, &dst);
	}
}

void	del_images(SDL_Surface **images)
{
	int		i;

	i = -1;
	while (images[++i] != NULL)
		SDL_FreeSurface(images[i]);
}

void	main_loop(SDL_Surface *screen)
{
	SDL_Surface	*images[3];
	SDL_Event	event;

	init_images(images);
	while (42)
	{
		put_images(screen, images);
		SDL_Flip(screen);
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			break ;
		else if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				break ;
	}
}

int		main(int argc, char* argv[])
{
	SDL_Surface	*screen;

	screen = NULL;
	init_window(&screen);
	if (screen == NULL)
		return (EXIT_FAILURE);
	main_loop(screen);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
