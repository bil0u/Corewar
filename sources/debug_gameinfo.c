/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_gameinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 03:12:38 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 01:48:17 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vcpu_types.h"
#include "corewar_types.h"
#include "corewar.h"
#include "corewar_verbose.h"
#include "memory_verbose.h"

static void	buff_players_stats(t_cwvm *vm, t_vmverb *vb)
{
	uint8_t		curr_player;
	uint8_t		p_len;
	t_player	*p;

	curr_player = 0;
	while (curr_player < vm->nb_players)
	{
		p = vm->players + vm->p_indexes[curr_player++];
		ft_sprintf(vb->color_buff[0], get_p_bgcolor(p->player_no));
		ft_sprintf(vb->color_buff[1], get_p_color(p->player_no));
		p_len = ft_strlen(p->header.prog_name);
		vb->bytes_used += ft_sprintf(vb->buff + vb->bytes_used, INF_PSTAT1,
			vb->color_buff[0], p->player_no);
		vb->bytes_used += ft_sprintf(vb->buff + vb->bytes_used,
			p_len > 22 ? INF_PNAMEL : INF_PNAME, vb->color_buff[1],
			p->header.prog_name);
		vb->bytes_used += ft_sprintf(vb->buff + vb->bytes_used, INF_PSTAT2,
			p->nb_processes, p->nb_lives, p->last_live);
	}
}

static void	buff_breakdown_bars(t_cwvm *vm, t_gamectrl *game, char *buff)
{
	uint8_t		curr_player;
	uint8_t		p_no;
	uint8_t		nb;
	uint8_t		ret;

	curr_player = 0;
	ret = 0;
	while (curr_player < vm->nb_players)
	{
		p_no = vm->p_indexes[curr_player++];
		ret += ft_sprintf(buff + ret, get_p_bgcolor(p_no + 1));
		nb = (vm->players[p_no].nb_lives * BATTLEBAR_LEN) / game->nb_lives;
		ft_memset(buff + ret, ' ', nb);
		ret += nb;
	}
}

void 		print_game_infos(t_cwvm *vm, t_vcpu *cpu, t_gamectrl *game)
{
	char		*cbreak;
	char		*lbreak;
	int32_t		next_chk;

	cbreak = vm->ctrl.verbose.curr_breakdown;
	lbreak = vm->ctrl.verbose.last_breakdown;
	next_chk = game->last_check + game->to_die - cpu->tick;
	vm->ctrl.verbose.bytes_used = 0;
	buff_players_stats(vm, &vm->ctrl.verbose);
	if (game->nb_lives == 0)
		ft_memset(cbreak + ft_sprintf(cbreak, BCOL_P0), ' ', BATTLEBAR_LEN);
	else
		buff_breakdown_bars(vm, game, cbreak);
	ft_sprintf(vm->ctrl.verbose.color_buff[0], get_p_bgcolor(game->winner));
	ft_sprintf(vm->ctrl.verbose.color_buff[1], get_p_color(game->winner));
	clear_window("inf");
	log_this("inf", 0, INF_MSG, cpu->tick, " ", vm->jobs.nb_processes,
		game->nb_lives, vm->ctrl.verbose.color_buff[0], game->winner,
		vm->ctrl.verbose.buff, cbreak, lbreak, game->to_die, game->nb_checks,
		MAX_CHECKS, game->last_check, next_chk);
}
