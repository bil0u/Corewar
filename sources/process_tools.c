/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:06:59 by upopee            #+#    #+#             */
/*   Updated: 2018/04/11 21:48:02 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "corewar.h"
#include "corewar_verbose.h"

/*
** -- PRINTS MEMORY ON STD
*/

int				dump_stop(t_cwdata *env, uint16_t flags, uint64_t *breakpoint)
{
	ft_printf((flags & CWF_DUMP ? CW_DUMPH : CW_SDMPH), env->cpu.tick);
	print_memory(env, NULL);
	if (flags & CWF_DUMP)
		return (TRUE);
	sleep(3);
	*breakpoint += env->control.nb_cycles;
	return (FALSE);
}

/*
** -- LOADS A PROCESS IN THE VCPU
*/

void			load_process(t_process *p, t_vcpu *cpu)
{
	cpu->pc = &(p->pc);
	cpu->carry = &(p->carry);
	cpu->registers = p->registers;
	cpu->curr_op = p->next_op;
	cpu->data.child_process = NULL;
	cpu->data.last_live = &(p->last_live);
	cpu->data.curr_player = p->player_no;
}

/*
** -- DELETE A GIVEN PROCESS FROM A PLAYER'S PROCESSES LIST
*/

static void		delete_process(t_list **p_list, t_list **prev,
									t_list **curr, t_process **p)
{
	t_list	*next;

	next = (*curr)->next;
	if (*prev != NULL)
		(*prev)->next = next;
	else
		*p_list = next;
	ft_memdel((void **)curr);
	ft_memdel((void **)p);
	*curr = next;
}

/*
** -- REFRESH THE PROCESS LIST : DELETE QUIET PROCESSES IF FOUND AND COUNT
**                               THE TOTAL NUMBER OF LIVES
*/

static uint32_t	update_process_list(t_cwdata *e, t_list **p_list, t_list *curr)
{
	uint32_t	nb_lives;
	t_process	*p;
	t_list		*prev;

	nb_lives = 0;
	prev = NULL;
	while (curr != NULL)
	{
		if ((p = (t_process *)curr->content)->last_live < e->control.last_check)
		{
			--(e->control.nb_processes);
			--(e->players[e->p_indexes[p->player_no - 1]].nb_processes);
			delete_process(p_list, &prev, &curr, &p);
		}
		else
		{
			++nb_lives;
			prev = curr;
			curr = curr->next;
		}
	}
	return (nb_lives);
}

/*
** -- FIND ALL QUIET PROCESSES AND CONSIDER THEM AS DEAD >> DELETED
*/

void			refresh_process_status(t_cwdata *env)
{
	uint8_t		curr_player;
	uint32_t	nb_lives;

	curr_player = 0;
	nb_lives = update_process_list(env, &env->processes, env->processes);
	if (nb_lives >= NBR_LIVE || env->control.max_checks == MAX_CHECKS)
	{
		env->control.to_die -= CYCLE_DELTA;
		env->control.max_checks = 0;
	}
	else
		++(env->control.max_checks);
	env->control.last_check = env->cpu.tick;
}
