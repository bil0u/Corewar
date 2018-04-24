/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:06:59 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 18:53:45 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "vm.h"
#include "vm_verbose.h"

/*
** -- DUPLICATE THE GIVEN PROCESS AND SET ITS VALUES TO MATCH ACTUAL CYCLE
*/

t_process	*dup_process(t_vcpu *cpu, t_player *pl, t_process *p, uint16_t init)
{
	t_jobctrl	*jobs;
	t_process	child;

	jobs = cpu->jobs;
	++pl->nb_processes;
	++jobs->nb_processes;
	ft_bzero(&child, sizeof(child));
	child.pid = ++cpu->jobs->next_pid;
	child.player_no = pl->player_no;
	child.pc = init;
	child.birth = p != NULL ? cpu->tick : 1;
	child.last_live = child.birth;
	if (p != NULL)
	{
		child.carry = p->carry;
		ft_memcpy(child.registers, p->registers, REG_LEN);
	}
	else
		child.registers[0] = REG_MAXVALUE - (child.player_no - 1);
	ft_lstadd(&jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	return ((t_process *)jobs->p_stack->content);
}

/*
** -- DELETE A GIVEN PROCESS FROM A PLAYER'S PROCESSES LIST
*/

int			player_exists(uint8_t player_no, t_gamectrl *g)
{
	uint8_t curr_p;

	curr_p = 0;
	while (curr_p < g->nb_players)
		if (g->players[g->p_indexes[curr_p++]].player_no == player_no)
			return (TRUE);
	return (FALSE);
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
			if (KILL_VERB)
				ft_printf(V_KILL, p->pid, V_SINCE, game->to_die);
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
	if (ctrl->flags & CWF_SLOW && jobs->nb_processes > 0)
		ctrl->sleep_time = 1000000 / (ctrl->cycles_sec * jobs->nb_processes);
	ctrl->verbose.bar_crop = BAR_CROP;
	ft_memcpy(ctrl->verbose.lbreakdown, ctrl->verbose.cbreakdown,
			BAR_BUFF_SIZE);
}
