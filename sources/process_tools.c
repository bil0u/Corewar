/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:06:59 by upopee            #+#    #+#             */
/*   Updated: 2018/04/12 06:48:48 by upopee           ###   ########.fr       */
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
	print_memory(env->arena, env->processes, NULL);
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
** -- REFRESH THE PROCESS LIST : DELETE QUIET PROCESSES IF FOUND
*/

static void		update_process_list(t_cwdata *env, t_pcontrol *ctrl,
										t_list **p_list, t_list *curr)
{
	t_process	*p;
	t_list		*prev;

	prev = NULL;
	while (curr != NULL)
	{
		if ((p = (t_process *)curr->content)->last_live < ctrl->last_check)
		{
			--(ctrl->nb_processes);
			--(env->players[env->p_indexes[p->player_no - 1]].nb_processes);
			delete_process(p_list, &prev, &curr, &p);
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

void			refresh_process_status(t_cwdata *env, t_pcontrol *ctrl)
{
	uint8_t		curr_player;

	curr_player = 0;
	update_process_list(env, ctrl, &env->processes, env->processes);
	if (ctrl->nb_lives >= NBR_LIVE || ctrl->nb_checks == MAX_CHECKS)
	{
		ctrl->to_die -= CYCLE_DELTA;
		ctrl->nb_checks = 0;
	}
	else
		++(ctrl->nb_checks);
	ctrl->nb_lives = 0;
	ctrl->last_check = env->cpu.tick;
}
