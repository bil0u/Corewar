/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:10:59 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 07:24:07 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_TYPES_H
# define SDL_TYPES_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"

# define PIX_X 				20
# define PIX_Y				18
# define WINDOW_W 			800
# define WINDOW_BIGW 		1280
# define WINDOW_H 			800
# define WINDOW_BIGH 		1152
# define BPP 				32
# define FPC 				sdlinfo->pc
# define F_WRITE 			sdlinfo->write
# define FNONE 				sdlinfo->none
# define DATA 				sdlinfo->data
# define GAMEMODE 			sdlinfo->game_mode
# define PLAYER 			sdlinfo->player
# define MAINSCREEN 		sdlinfo->screen
# define MEM_ZONE 			sdlinfo->mem_zone
# define EVENT_TYPE 		sdlinfo->event.type
# define EVENT_KEY 			sdlinfo->event.key.keysym.sym
# define BKGROUND_POS 		sdlinfo->background_pos
# define TITLES_POS 		sdlinfo->title_pos
# define PRESS_POS 			sdlinfo->press_pos
# define CREDIT_POS 		sdlinfo->credit_pos
# define MAIN_POS 			sdlinfo->main_pos
# define NAVI_POS 			sdlinfo->navi_pos
# define BKGROUND_SCREEN 	sdlinfo->background
# define TITLE_SCREEN 		sdlinfo->title
# define NAVI 				sdlinfo->navi
# define CUR_X 				sdlinfo->x
# define CUR_Y 				sdlinfo->y

// BIS_SET(vm->a_flags[i], CWCF_PCNO(player_1))

typedef struct		s_sdl
{
	uint8_t			game_mode;
	uint8_t			none;
	uint8_t			player;
	uint8_t			pc;
	uint8_t			write;
	int				y;
	int				x;
	uint8_t			*data;
	SDL_Surface		*screen;
	SDL_Surface		*background;
	SDL_Surface		*title;
	SDL_Surface		*mem_zone;
	SDL_Surface		*navi;
	SDL_Event		event;
	SDL_Rect		main_pos;
	SDL_Rect		title_pos;
	SDL_Rect		press_pos;
	SDL_Rect		background_pos;
	SDL_Rect		credit_pos;
	SDL_Rect		navi_pos;
	TTF_Font		*police_game;
	TTF_Font		*police_start_screen;
	SDL_Color		txt_color;
	SDL_Color		bg_color;
	SDL_Color		black;
	SDL_Color		white;
	SDL_Color		red;
	SDL_Color		pc_red;
	SDL_Color		blue;
	SDL_Color		pc_blue;
	SDL_Color		green;
	SDL_Color		pc_green;
	SDL_Color		yellow;
	SDL_Color		pc_yellow;
	SDL_Color		grey;
	int				save;
}					t_sdl;

/*
** -- INIT FUNCTIONS
*/

int					init_sdl(t_sdl *sdlinfo);
int					quit_sdl(t_sdl *sdlinfo);

/*
** -- TTF INIT FUNCTIONS
*/

int					ttf_init(t_sdl *sdlinfo);
void				init_ttf_color(t_sdl *sdlinfo);
void				init_ttf_pc_color(t_sdl *sdlinfo);

/*
** -- SDL MAIN FUNCTIONS
*/

int					main_screen(t_sdl *sdlinfo);
int					start_screen(t_sdl *sdlinfo);
int					start_screen_set(t_sdl *sdlinfo);
int					title_screen(t_sdl *sdlinfo);
int					title_screen_set(t_sdl *sdlinfo);
int					title_screen_set_sup(t_sdl *sdlinfo);
int					main_screen_update(t_sdl *sdlinfo);
int					sdl_free(SDL_Surface *tofree1, SDL_Surface *tofree2,
					SDL_Surface *tofree3);

int					sdl_clean(t_sdl *sdlinfo, int resize, int surface_free);

int					event_handler(t_sdl *sdlinfo);
int					title_event_handler(t_sdl *sdlinfo);
void				navigation_key_handler(t_sdl *sdlinfo);

void				get_block_color(t_sdl *sdlinfo);
void				get_txt_color(t_sdl *sdlinfo);
void				test_pc_player(t_sdl *sdlinfo, int y);
void				get_wrt_txt_color(t_sdl *sdlinfo);
int					set_flags(t_sdl *sdlinfo);

#endif
