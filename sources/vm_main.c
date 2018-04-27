/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/27 19:08:08 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "vm_verbose.h"
#include "cpu_debug.h"
#include "vm_debug.h"

/*
** -- INITIALIZE THE MAIN ENVIRONMENT AND THE LOG WINDOWS
*/

static int	init_vm(int argc, char **argv, t_cwvm *vm)
{
	ft_bzero(vm, sizeof(*vm));
	if (check_argv(argc, argv, vm) != SUCCESS)
		return (FAILURE);
	vm->cpu.memory = vm->arena;
	vm->cpu.m_flags = vm->a_flags;
	vm->cpu.jobs = &vm->jobs;
	vm->cpu.ctrl = &vm->ctrl;
	return (SUCCESS);
}

/*
** -- INITIALIZE THE NEEDED ELEMENTS FOR LAUNCHING THE GAME
*/

static void	init_parameters(t_cwvm *vm, t_vmctrl *c, t_jobctrl *j)
{
	uint8_t		ret;

	c->verbose.bar_crop = BAR_CROP;
	ret = ft_sprintf(c->verbose.lbreakdown, "{b_black}");
	ft_memset(c->verbose.lbreakdown + ret, ' ', BAR_LEN);
	if (c->flags & CWF_DEBUG && c->d_level != CWDL_NONE && c->cycles_sec == 0
	&& BSET(c->flags, CWF_SLOW))
		c->cycles_sec = CPS_DEFAULT;
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
	c->d_level & CWDL_REG ? debug_registers(&c->verbose, j->p_stack) : 0;
}

static void	init_data(t_cwvm *vm)
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
	init_parameters(vm, c, j);
	sleep(1);
}

/*
** -- FREE ALLOCATED ELEMENTS AND DECLARE WINNER
*/

static void	end_game(t_cwvm *v, t_vmctrl *c, t_jobctrl *j, uint8_t dumped)
{
	char		*name;
	uint8_t		winner;
	int			i;

	c->d_level & CWDL_MEM ? debug_memory(v->arena, v->a_flags, MEM_WIN) : 0;
	c->d_level & CWDL_INF ? debug_infos(v, &v->cpu, &v->game, &c->verbose) : 0;
	i = -1;
	winner = v->game.winner;
	name = NULL;
	while (++i < v->nb_players)
		if (v->players[v->p_indexes[i]].player_no == winner)
		{
			name = v->players[v->p_indexes[i]].header.pname;
			break ;
		}
	ft_lstdel(&j->p_stack, &ft_delcontent);
	if (dumped == FALSE)
		ft_printf((c->flags & CWF_VERB ? CW_ZWINNER_IS : CW_WINNER_IS),
			winner, name);
}

/*
** -- RUN THE CPU FOR A SET CYCLES NUMBER OR UNTIL A WINNER IS FOUND,
**    DEPENDING ON GIVEN OPTIONS
*/

static int	run_cpu(t_cwvm *vm, t_vcpu *cpu, t_gamectrl *g, t_jobctrl *j)
{
	uint32_t	breakpoint;
	t_list		*curr;
	t_process	*p;
	t_vmctrl	*c;

	c = &vm->ctrl;
	breakpoint = vm->ctrl.dump_cycles;
	while (j->nb_processes > 0 && ++cpu->tick)
	{
		CYCL_VERB ? ft_printf(V_CYCLE, cpu->tick) : 0;
		INF_DEB ? debug_infos(vm, cpu, g, &c->verbose) : 0;
		curr = j->p_stack;
		while (curr != NULL)
		{
			p = (t_process *)curr->content;
			exec_or_wait(cpu, p, vm->players + (p->player_no - 1), g);
			PROC_DEB ? debug_processes(vm, j->p_stack, j) : 0;
			RUN_SLOW ? usleep(c->sleep_time) : 0;
			curr = curr->next;
		}
		if (cpu->tick == breakpoint && dump_stop(vm, &breakpoint) == TRUE)
			return (TRUE);
		cpu->tick >= g->last_check + g->to_die ? check_gstate(vm, g, j, c) : 0;
	}
	return (FALSE);
}

int			main(int argc, char **argv)
{
	t_cwvm		vm;
	uint8_t		ret;

	if (argc == 1 || ft_strequ(argv[1], "-h"))
		return (err_msg(CW_USAGE));
	if (init_vm(argc, argv, &vm) != SUCCESS)
		return (err_msg(CWE_HELP));
	load_players(&vm);
	init_data(&vm);
	ret = run_cpu(&vm, &vm.cpu, &vm.game, &vm.jobs);
	end_game(&vm, &vm.ctrl, &vm.jobs, ret);
	return (SUCCESS);
}
