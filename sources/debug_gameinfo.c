/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_gameinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 03:12:38 by upopee            #+#    #+#             */
/*   Updated: 2018/05/01 19:32:35 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "vm.h"
#include "vm_debug.h"

/*
** -- FILL VERBOSE BUFFER WITH PLAYERS INFORMATIONS
*/

static void		buff_players_buff(t_cwvm *vm, t_vmverb *v)
{
	uint8_t		curr_player;
	uint8_t		p_len;
	t_player	*p;

	curr_player = 0;
	v->bytes_used = 0;
	while (curr_player < vm->nb_players)
	{
		p = vm->players + vm->p_indexes[curr_player++];
		ft_sprintf(v->color_buff[0], get_p_bgcolor(p->player_no));
		ft_sprintf(v->color_buff[1], get_p_color(p->player_no));
		p_len = ft_strlen(p->header.pname);
		v->bytes_used += ft_sprintf(v->buff + v->bytes_used, INF_PSTAT1,
			v->color_buff[0], p->player_no);
		v->bytes_used += ft_sprintf(v->buff + v->bytes_used,
			p_len > 19 ? INF_PNAMEL : INF_PNAME, v->color_buff[1],
			p->header.pname);
		v->bytes_used += ft_sprintf(v->buff + v->bytes_used, INF_PSTAT2,
			p->nb_processes, p->nb_lives, p->last_live);
	}
}

/*
** -- FILL BREAKDOWN BARS BUFFER WITH CURRENT LIVE'S STATE
*/

static uint8_t	buff_breakdown(t_cwvm *vm, t_vmverb *v, char *bar, uint32_t nbl)
{
	float		nb_sp;
	uint8_t		curr_player;
	uint8_t		p;
	uint8_t		ret;

	curr_player = 0;
	ret = 0;
	v->verb_carry = 0.0;
	while (curr_player < vm->nb_players)
	{
		p = vm->p_indexes[curr_player++];
		ret += ft_sprintf(bar + ret, get_p_bgcolor(p + 1));
		nb_sp = (float)(vm->players[p].nb_lives * (BAR_LEN - v->bar_crop));
		nb_sp /= (float)nbl;
		v->verb_carry += modff(nb_sp, &nb_sp) + 0.001;
		if (v->verb_carry >= 1.0 && (nb_sp += 1.0))
			v->verb_carry -= 1.0;
		ft_memset(bar + ret, ' ', (size_t)nb_sp);
		ret += nb_sp;
	}
	return (ret);
}

/*
** -- FILL BREAKDOWN BARS AND COMMENTS FOR THE GAME INFOS
*/

static void		fill_curr_bar(t_cwvm *vm, t_vmverb *v, char *bar, uint32_t nbl)
{
	uint8_t		margin;
	uint8_t		ret;

	ft_bzero(bar, BAR_BUFF_SIZE);
	ft_bzero(v->comment, BAR_BUFF_SIZE);
	if (nbl == 0 && (ret = ft_sprintf(bar, BCOL_P0)))
		ft_memset(bar + ret, ' ', BAR_LEN);
	else if (v->bar_crop > 0)
	{
		margin = v->bar_crop / 2;
		ret = ft_sprintf(bar, BCOL_P0);
		ft_memset(bar + ret, ' ', margin);
		ret += margin;
		ret += buff_breakdown(vm, v, bar + ret, nbl);
		ret += ft_sprintf(bar + ret, BCOL_P0);
		ft_memset(bar + ret, ' ', margin);
		v->bar_crop -= CROP_SPEED;
	}
	else
		buff_breakdown(vm, v, bar, nbl);
	if (nbl == 0)
		ft_sprintf(v->comment, COMMENT_NOONE);
	else
		ft_sprintf(v->comment, (vm->game.alpha ? COMMENT_ALPHA : COMMENT_FIGHT),
			vm->players[vm->game.alpha - 1].header.pname);
}

/*
** -- DISLPAY GAME INFORMATIONS
*/

void			debug_infos(t_cwvm *vm, t_vcpu *c,
											t_gamectrl *g, t_vmverb *v)
{
	char		*curr_break;
	char		*last_break;

	curr_break = v->cbreakdown;
	last_break = v->lbreakdown;
	buff_players_buff(vm, v);
	fill_curr_bar(vm, v, curr_break, g->valid_lives);
	ft_sprintf(v->color_buff[0], get_p_bgcolor(g->winner));
	ft_sprintf(v->color_buff[1], get_p_color(vm->game.alpha));
	clear_window(INF_WIN);
	log_this(IWA, INF_MSG, c->tick, " ", vm->jobs.nb_processes,
		g->valid_lives, v->color_buff[0], g->winner, v->buff,
		v->color_buff[1], v->comment, curr_break, last_break,
		g->to_die, g->nb_checks, MAX_CHECKS, g->last_check,
		(g->last_check + g->to_die - c->tick));
}
