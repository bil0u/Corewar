/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:06:59 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 06:28:06 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"
#include "vm.h"
#include "vm_verbose.h"
#include "vm_debug.h"

/*
** -- DUPLICATE THE GIVEN PROCESS, INIT IF NONE GIVEN
*/

t_process	*dup_process(t_vcpu *cpu, t_player *pl, t_process *p, uint16_t init)
{
	t_jobctrl	*jobs;
	t_process	child;

	jobs = cpu->jobs;
	ft_bzero(&child, sizeof(child));
	child.birth = cpu->tick;
	child.pid = ++jobs->next_pid;
	child.pc = init;
	if (p != NULL)
	{
		child.player_no = p->player_no;
		child.last_live = p->last_live;
		child.carry = p->carry;
		ft_memcpy(child.registers, p->registers, REG_LEN);
	}
	else
	{
		child.player_no = pl->player_no;
		child.registers[0] = REG_MAXVALUE - (child.player_no - 1);
	}
	BSET(cpu->m_flags[init], CWCF_PCNO(child.player_no));
	++pl->nb_processes;
	++jobs->nb_processes;
	ft_lstadd(&jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	return (jobs->p_stack ? (t_process *)jobs->p_stack->content : NULL);
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
	ft_memdel((void **)p);
	ft_memdel((void **)curr);
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
		p = (t_process *)curr->content;
		if (p->last_live <= game->last_check || game->to_die < 0)
		{
			--(jobs->nb_processes);
			--(vm->players[p->player_no - 1].nb_processes);
			if (KILL_VERB)
				ft_printf(V_KILL, p->pid, V_SINCE, game->to_die);
			BUNSET(vm->a_flags[p->pc], CWCF_PCNO(p->player_no));
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

void		check_gstate(t_cwvm *vm, t_gamectrl *g, t_jobctrl *j, t_vmctrl *c)
{
	uint8_t		curr_player;

	refresh_pstack(vm, g, j, j->p_stack);
	++g->nb_checks;
	if (g->tot_lives >= NBR_LIVE || g->nb_checks == MAX_CHECKS)
	{
		g->to_die -= CYCLE_DELTA;
		g->nb_checks = 0;
		CYCL_VERB ? ft_printf(V_CYCLETD, g->to_die) : 0;
	}
	g->last_check = vm->cpu.tick;
	g->tot_lives = 0;
	g->valid_lives = 0;
	curr_player = 0;
	while (curr_player < vm->nb_players)
		vm->players[vm->p_indexes[curr_player++]].nb_lives = 0;
	if (c->flags & CWF_SLOW && j->nb_processes > 0)
		c->sleep_time = 1000000 / (c->cycles_sec * j->nb_processes);
	c->verbose.bar_crop = BAR_CROP;
	ft_memcpy(c->verbose.lbreakdown, c->verbose.cbreakdown, BAR_BUFF_SIZE);
}
