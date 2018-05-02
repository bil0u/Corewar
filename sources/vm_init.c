/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:25:19 by upopee            #+#    #+#             */
/*   Updated: 2018/05/02 00:04:15 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_debug.h"
#include "vm_debug.h"

/*
** -- INITIALIZE THE MAIN ENVIRONMENT AND THE LOG WINDOWS
*/

int				init_vm(int argc, char **argv, t_cwvm *vm)
{
	ft_bzero(vm, sizeof(*vm));
	if (check_argv(argc, argv, vm) != SUCCESS)
		return (FAILURE);
	vm->cpu.memory = vm->arena;
	vm->cpu.m_flags = vm->a_flags;
	vm->cpu.jobs = &vm->jobs;
	vm->cpu.ctrl = &vm->ctrl;
	tcgetattr(STDIN_FILENO, &vm->ctrl.t_info);
	vm->ctrl.t_save = vm->ctrl.t_info;
	vm->ctrl.t_info.c_lflag &= ~(ECHO | ICANON);
	vm->ctrl.t_info.c_cc[VMIN] = 0;
	vm->ctrl.t_info.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &vm->ctrl.t_info);
	return (SUCCESS);
}

/*
** -- INITIALIZE THE NEEDED ELEMENTS FOR LAUNCHING THE GAME
*/

static void		init_parameters(t_cwvm *vm, t_vmctrl *c,
									t_jobctrl *j, t_vmverb *v)
{
	uint8_t		ret;

	v->bar_crop = BAR_CROP;
	ret = ft_sprintf(v->lbreakdown, BAR_ECOLOR);
	ft_memset(v->lbreakdown + ret, ' ', BAR_LEN);
	if (c->flags & CWF_DEBUG && c->d_level != CWDL_NONE)
	{
		if (c->cycles_sec == 0 && BSET(c->flags, CWF_SLOW))
			c->cycles_sec = CPS_DEFAULT;
		c->paused = TRUE;
	}
	if (c->flags & CWF_SLOW)
		c->sleep_time = 1000000 / (c->cycles_sec * j->nb_processes);
	c->d_level & CWDL_INF ? new_logwindow(INF_WIN, WF_KEEP | WF_CLOSE) : 0;
	c->d_level & CWDL_INS ? new_logwindow(INS_WIN, WF_KEEP | WF_CLOSE) : 0;
	c->d_level & CWDL_ARG ? new_logwindow(ARG_WIN, WF_KEEP | WF_CLOSE) : 0;
	c->d_level & CWDL_MEM ? new_logwindow(MEM_WIN, WF_KEEP | WF_CLOSE) : 0;
	c->d_level & CWDL_REG ? new_logwindow(REG_WIN, WF_KEEP | WF_CLOSE) : 0;
	c->d_level & CWDL_PROC ? new_logwindow(PROC_WIN, WF_KEEP | WF_CLOSE) : 0;
	c->d_level & CWDL_PROC ? debug_processes(vm, j->p_stack, j) : 0;
	c->d_level & CWDL_MEM ? debug_memory(vm->arena, vm->a_flags, MEM_WIN) : 0;
	c->d_level & CWDL_REG ? debug_registers(v, j->p_stack) : 0;
	c->d_level & CWDL_REG ? debug_registers(v, j->p_stack) : 0;
	c->d_level & CWDL_INF ? debug_infos(vm, &vm->cpu, &vm->game, v) : 0;
}

void			init_data(t_cwvm *vm)
{
	t_vmctrl	*c;
	t_jobctrl	*j;
	t_gamectrl	*g;

	c = &vm->ctrl;
	j = &vm->jobs;
	g = &vm->game;
	g->nb_players = vm->nb_players;
	g->p_indexes = vm->p_indexes;
	g->players = vm->players;
	g->to_die = CYCLE_TO_DIE;
	g->winner = g->p_indexes[g->nb_players - 1] + 1;
	j->nb_processes = j->next_pid;
	init_parameters(vm, c, j, &c->verbose);
}
