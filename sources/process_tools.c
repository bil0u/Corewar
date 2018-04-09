/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:06:59 by upopee            #+#    #+#             */
/*   Updated: 2018/04/09 05:39:03 by upopee           ###   ########.fr       */
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
}

/*
** -- DELETE A GIVEN PROCESS FROM A PLAYER'S PROCESSES LIST
*/

static void		delete_process(t_player *pl, t_process **pr,
												t_list **prev, t_list **curr)
{
	if (*prev != NULL)
		(*prev)->next = (*curr)->next;
	else
		pl->processes = (*curr)->next;
	if (*curr == pl->pending)
		pl->pending = pl->pending->next ? pl->pending->next : pl->processes;
	ft_memdel((void **)pr);
	ft_memdel((void **)curr);
	*curr = *prev ? (*prev)->next : pl->processes;
	--pl->nb_processes;
}

/*
** -- SEARCH FOR DEAD PROCESSES FOR THE CURRENT PLAYER, AND DELETE THEM IF FOUND
*/

static uint32_t	check_pstatus(t_player *player, t_pcontrol *ctrl)
{
	uint32_t	nb_lives;
	t_list		*curr;
	t_list		*prev;
	t_process	*process;

	nb_lives = 0;
	prev = NULL;
	curr = player->processes;
	while (curr != NULL)
	{
		process = (t_process *)curr->content;
		if (process->last_live <= ctrl->last_check)
		{
			delete_process(player, &process, &prev, &curr);
			ctrl->nb_processes--;
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

void			kill_quiet_processes(t_cwdata *env)
{
	uint8_t		curr_player;
	uint32_t	nb_lives;

	curr_player = 0;
	nb_lives = 0;
	while (curr_player < env->nb_players)
		nb_lives += check_pstatus(env->players + curr_player++, &env->control);
	if (nb_lives >= NBR_LIVE || env->control.max_checks == MAX_CHECKS)
	{
		env->control.to_die -= CYCLE_DELTA;
		env->control.max_checks = 0;
	}
	else
		++(env->control.max_checks);
	env->control.last_check = env->cpu.tick;
}
