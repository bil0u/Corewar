/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:04:17 by upopee            #+#    #+#             */
/*   Updated: 2018/04/10 22:15:01 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "sdl_test.h"

void	exit_error(char *prompt, char *err_msg)
{
	printf("%s: %s\n", prompt, err_msg);
	Mix_CloseAudio();
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void	init_window(SDL_Surface **screen)
{
	SDL_Surface	*icon;
	uint32_t	win_flags;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != -1)
	{
		icon = IMG_Load(IMG_LOGO);
		SDL_WM_SetIcon(icon, NULL);
		SDL_FreeSurface(icon);
		win_flags = SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF;
		*screen = SDL_SetVideoMode(WINSZ_X, WINSZ_Y, 32, win_flags);
		if (*screen != NULL)
		{
			SDL_WM_SetCaption(WIN_NAME, NULL);
			if (Mix_OpenAudio(DEF_FREQ, MIX_DEFAULT_FORMAT, 2, CHK_SIZE) == -1)
				exit_error("Mix_OpenAudio()", Mix_GetError());
		}
		else
			exit_error("SDL_SetVideoMode()", SDL_GetError());
	}
	else
		exit_error("SDL_Init()", SDL_GetError());
}

/*
** ----------------------------- IMAGES ---------------------------------------
*/

void 	init_images(SDL_Surface **images)
{
	images[0] = IMG_Load(IMG_BG);
	images[1] = NULL; //IMG_Load(IMG_LOGO);
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

/*
** ----------------------------- AUDIO ----------------------------------------
*/

void	init_audio(Mix_Music **music, Mix_Chunk **effects)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME >> 1);
	*music = Mix_LoadMUS(MUS_OPENING);
	Mix_AllocateChannels(NB_EFFECTS);
	Mix_Volume(0, MIX_MAX_VOLUME >> 1);
	effects[0] = Mix_LoadWAV(EFF_HEADSHOT);
	Mix_Volume(1, MIX_MAX_VOLUME >> 1);
	effects[1] = Mix_LoadWAV(EFF_SNIPER);
	Mix_Volume(2, MIX_MAX_VOLUME >> 1);
	effects[2] = Mix_LoadWAV(EFF_MONSTERK);
	effects[NB_EFFECTS] = NULL;
	Mix_PlayMusic(*music, -1);
	Mix_PauseMusic();
}

void	del_audio(Mix_Music *music, Mix_Chunk **effects)
{
	int		i;

	i = -1;
	while (effects[++i] != NULL)
		Mix_FreeChunk(effects[i]);
	Mix_FreeMusic(music);
}

/*
** ----------------------------------------------------------------------------
*/

void	main_loop(SDL_Surface *screen)
{
	SDL_Surface	*images[NB_IMAGES + 1];
	Mix_Music	*music;
	Mix_Chunk	*effects[NB_EFFECTS + 1];
	SDL_Event	event;

	init_images(images);
	init_audio(&music, effects);
	while (42)
	{
		put_images(screen, images);
		SDL_Flip(screen);
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			break ;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				break ;
			else if (event.key.keysym.sym == SDLK_SPACE)
				Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
			else if (event.key.keysym.sym == SDLK_BACKSPACE)
				Mix_RewindMusic();
			else if (event.key.keysym.sym == SDLK_1)
				Mix_PlayChannel(0, effects[0], 0);
			else if (event.key.keysym.sym == SDLK_2)
				Mix_PlayChannel(1, effects[1], 0);
			else if (event.key.keysym.sym == SDLK_3)
				Mix_PlayChannel(2, effects[2], 0);
		}
	}
	del_images(images);
	del_audio(music, effects);
}

int		main(int argc, char* argv[])
{
	SDL_Surface	*screen;

	screen = NULL;
	init_window(&screen);
	if (screen == NULL)
		return (EXIT_FAILURE);

	main_loop(screen);

	Mix_CloseAudio();
	SDL_Quit();
	return (EXIT_SUCCESS);
}
