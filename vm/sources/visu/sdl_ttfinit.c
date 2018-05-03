/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_ttfinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 18:31:03 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 17:06:39 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"

int			ttf_init(t_sdl *sdlinfo)
{
	sdlinfo->police_game = NULL;
	sdlinfo->police_start_screen = NULL;
	if (TTF_Init() == FAILURE)
		return (FAILURE);
	sdlinfo->police_game = TTF_OpenFont(FONT_GAME, FONT_SZGM);
	sdlinfo->police_start_screen = TTF_OpenFont(FONT_SCRN, FONT_SZSC);
	if (sdlinfo->police_game == NULL || sdlinfo->police_start_screen == NULL)
		return (FAILURE);
	init_ttf_color(sdlinfo);
	init_ttf_pc_color(sdlinfo);
	return (SUCCESS);
}

void		init_ttf_color(t_sdl *sdlinfo)
{
	sdlinfo->black.r = 0;
	sdlinfo->black.g = 0;
	sdlinfo->black.b = 0;
	sdlinfo->white.r = 215;
	sdlinfo->white.g = 215;
	sdlinfo->white.b = 215;
	sdlinfo->red.r = 193;
	sdlinfo->red.g = 46;
	sdlinfo->red.b = 46;
	sdlinfo->blue.r = 56;
	sdlinfo->blue.g = 86;
	sdlinfo->blue.b = 209;
	sdlinfo->green.r = 93;
	sdlinfo->green.g = 188;
	sdlinfo->green.b = 41;
	sdlinfo->yellow.r = 216;
	sdlinfo->yellow.g = 170;
	sdlinfo->yellow.b = 32;
	sdlinfo->grey.r = 165;
	sdlinfo->grey.g = 165;
	sdlinfo->grey.b = 192;
	sdlinfo->bg_grey.r = 42;
	sdlinfo->bg_grey.g = 42;
	sdlinfo->bg_grey.b = 42;
}

void		init_ttf_pc_color(t_sdl *sdlinfo)
{
	sdlinfo->pc_red.r = 255;
	sdlinfo->pc_red.g = 50;
	sdlinfo->pc_red.b = 50;
	sdlinfo->pc_blue.r = 91;
	sdlinfo->pc_blue.g = 159;
	sdlinfo->pc_blue.b = 255;
	sdlinfo->pc_green.r = 89;
	sdlinfo->pc_green.g = 255;
	sdlinfo->pc_green.b = 0;
	sdlinfo->pc_yellow.r = 255;
	sdlinfo->pc_yellow.g = 224;
	sdlinfo->pc_yellow.b = 86;
}
