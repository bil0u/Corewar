/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susivagn <susivagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 18:34:10 by susivagn          #+#    #+#             */
/*   Updated: 2018/05/03 15:31:47 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"
#include "vm.h"

static void		set_basics(t_sdl *info)
{
	info->bg_color = info->bg_grey;
	if (info->pc_no == 0)
		info->txt_color = info->white;
	else
		info->txt_color = info->black;
}

void			set_flags(t_sdl *info, uint8_t ar, uint16_t af)
{
	info->rwrite = af & 1;
	info->player_no = get_pno(((af >> NB_CFLAGS) & 0xF));
	info->pc_no = get_pno(((af >> CWCF_PCSHIFT) & 0xF));
	ft_sprintf(info->data, "%.2hhx", ar);
}

void			get_block_color(t_sdl *info)
{
	if (info->pc_no == 0)
		if (info->rwrite == 1)
		{
			info->player_no == 1 ? info->bg_color = info->blue : (void)0;
			info->player_no == 2 ? info->bg_color = info->yellow : (void)0;
			info->player_no == 3 ? info->bg_color = info->red : (void)0;
			info->player_no == 4 ? info->bg_color = info->green : (void)0;
		}
		else
		{
			info->player_no == 1 ? info->bg_color = info->blue : (void)0;
			info->player_no == 2 ? info->bg_color = info->yellow : (void)0;
			info->player_no == 3 ? info->bg_color = info->red : (void)0;
			info->player_no == 4 ? info->bg_color = info->green : (void)0;
		}
	else
	{
		info->pc_no == 0 ? info->bg_color = info->white : (void)0;
		info->pc_no == 1 ? info->bg_color = info->pc_blue : (void)0;
		info->pc_no == 2 ? info->bg_color = info->pc_yellow : (void)0;
		info->pc_no == 3 ? info->bg_color = info->pc_red : (void)0;
		info->pc_no == 4 ? info->bg_color = info->pc_green : (void)0;
	}
}

void			get_txt_color(t_sdl *info)
{
	set_basics(info);
	if (info->pc_no == 0)
		if (info->rwrite == 1)
		{
			info->player_no == 1 ? info->txt_color = info->pc_blue : (void)0;
			info->player_no == 2 ? info->txt_color = info->pc_yellow : (void)0;
			info->player_no == 3 ? info->txt_color = info->pc_red : (void)0;
			info->player_no == 4 ? info->txt_color = info->pc_green : (void)0;
		}
		else
		{
			info->player_no == 1 ? info->txt_color = info->blue : (void)0;
			info->player_no == 2 ? info->txt_color = info->yellow : (void)0;
			info->player_no == 3 ? info->txt_color = info->red : (void)0;
			info->player_no == 4 ? info->txt_color = info->green : (void)0;
		}
	else
	{
		info->pc_no == 0 ? info->bg_color = info->white : (void)0;
		info->pc_no == 1 ? info->bg_color = info->blue : (void)0;
		info->pc_no == 2 ? info->bg_color = info->yellow : (void)0;
		info->pc_no == 3 ? info->bg_color = info->red : (void)0;
		info->pc_no == 4 ? info->bg_color = info->green : (void)0;
	}
}
