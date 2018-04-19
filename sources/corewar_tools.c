/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:06:59 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 16:41:11 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vcpu_types.h"
#include "corewar_types.h"
#include "corewar.h"
#include "corewar_verbose.h"

/*
** -- PRINTS MEMORY ON STD
*/

int			dump_stop(t_cwvm *vm, int32_t *breakpoint)
{
	ft_printf((vm->ctrl.flags & CWF_SDMP ? CW_SDMPH : CW_DUMPH), vm->cpu.tick);
	print_memory(vm->arena, vm->jobs.p_stack, NULL);
	if (vm->ctrl.flags & CWF_SDMP)
	{
		sleep(DUMP_WAIT);
		*breakpoint += vm->ctrl.dump_cycles;
		return (FALSE);
	}
	return (TRUE);
}

/*
** -- DELETE A GIVEN PROCESS FROM A PLAYER'S PROCESSES LIST
*/

static void	delete_process(t_list **p_stack, t_list **prev,
									t_list **curr, t_process **p)
{
	t_list	*next;

	next = (*curr)->next;
	if (*prev != NULL)
		(*prev)->next = next;
	else
		*p_stack = next;
	ft_memdel((void **)curr);
	ft_memdel((void **)p);
	*curr = next;
}

/*
** -- REFRESH THE PROCESS LIST : DELETE QUIET PROCESSES IF FOUND
*/

static void	refresh_pstack(t_cwvm *vm, t_gamectrl *game,
										t_jobctrl *jobs, t_list *curr)
{
	t_process	*p;
	t_list		*prev;

	prev = NULL;
	while (curr != NULL)
	{
		if ((p = (t_process *)curr->content)->last_live <= game->last_check)
		{
			--(jobs->nb_processes);
			--(vm->players[p->player_no - 1].nb_processes);
			delete_process(&jobs->p_stack, &prev, &curr, &p);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

/*
** -- DELETE QUIET PROCESSES IF THERE'S ANY AND MODIFY GAME VARIABLES
*/

void		check_gamestatus(t_cwvm *vm)
{
	t_gamectrl	*game;
	t_jobctrl	*jobs;
	t_vmctrl	*ctrl;
	uint8_t		curr_player;

	game = &vm->game;
	jobs = &vm->jobs;
	ctrl = &vm->ctrl;
	refresh_pstack(vm, game, jobs, jobs->p_stack);
	++(game->nb_checks);
	if (game->nb_lives >= NBR_LIVE || game->nb_checks == MAX_CHECKS)
	{
		game->to_die -= CYCLE_DELTA;
		game->nb_checks = 0;
	}
	curr_player = 0;
	while (curr_player < vm->nb_players)
		vm->players[vm->p_indexes[curr_player++]].nb_lives = 0;
	game->nb_lives = 0;
	game->last_check = vm->cpu.tick;
	ctrl->sleep_time = 1000000 / (ctrl->cycles_sec * jobs->nb_processes);
	ctrl->verbose.bar_crop = BAR_CROP;
	ft_memcpy(ctrl->verbose.lbreakdown, ctrl->verbose.cbreakdown,
			BAR_BUFF_SIZE);
}
