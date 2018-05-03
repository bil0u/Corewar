/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 13:40:21 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "vm_verbose.h"
#include "vm_debug.h"

/*
** -- FREE ALLOCATED ELEMENTS
*/

static int		del_env(t_cwvm *v, t_vmctrl *c, t_jobctrl *j)
{
	ft_lstdel(&j->p_stack, &ft_delcontent);
	if (VISU_SDL)
		quit_sdl(&v->visu);
	tcsetattr(STDIN_FILENO, TCSANOW, &c->t_save);
	return (SUCCESS);
}

/*
** -- DECLARE WINNER
*/

static void		end_game(t_cwvm *v, t_vmctrl *c, t_jobctrl *j, uint8_t dumped)
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
	if (dumped == FALSE && c->stop == FALSE)
		ft_printf((c->flags & CWF_VERB ? CW_ZWINNER_IS : CW_WINNER_IS),
			winner, name);
	del_env(v, c, j);
}

/*
** -- COMSUME AN EXEC STEP FOR EACH PROCESS IN THE VM P_STACK
*/

static void		consume_cycle(t_cwvm *vm, t_vcpu *cpu,
								t_gamectrl *g, t_jobctrl *j)
{
	t_vmctrl	*c;
	t_list		*curr;
	t_process	*p;

	curr = j->p_stack;
	c = &vm->ctrl;
	cpu->b_read = 0;
	while (curr != NULL)
	{
		p = (t_process *)curr->content;
		exec_or_wait(cpu, p, vm->players + (p->player_no - 1), g);
		RUN_SLOW ? usleep(c->sleep_time) : 0;
		curr = curr->next;
	}
	PROC_DEB ? debug_processes(vm, j->p_stack, j) : 0;
	MEM_DEB && cpu->b_read > 0 ? debug_memory(MDA, MEM_WIN) : 0;
}

/*
** -- RUN THE VCPU UNTIL A WINNER IS FOUND OR UTIL DUMP CYCLE NO IS REACHED
*/

static int		run_cpu(t_cwvm *vm, t_vcpu *cpu, t_gamectrl *g, t_jobctrl *j)
{
	uint32_t	breakpoint;
	t_vmctrl	*c;

	c = &vm->ctrl;
	breakpoint = vm->ctrl.dump_cycles;
	while (j->nb_processes > 0 && c->stop == FALSE)
	{
		VISU_SDL ? main_screen(&vm->visu, vm->arena, vm->a_flags, c) : 0;
		if (read(STDIN_FILENO, &c->key, 1) > 0 && c->key == ' ')
			c->paused = !(c->paused);
		if ((c->paused == FALSE || c->key == '\n') && (c->key = 0) == 0)
		{
			++cpu->tick;
			CYCL_VERB ? ft_printf(V_CYCLE, cpu->tick) : 0;
			INF_DEB ? debug_infos(vm, cpu, g, &c->verbose) : 0;
			consume_cycle(vm, cpu, g, j);
			if (cpu->tick == breakpoint && dump_stop(vm, &breakpoint) == TRUE)
				return (TRUE);
			if (TOI32(cpu->tick - g->last_check) >= g->to_die)
				check_gstate(vm, g, j, c);
		}
		else
			usleep(1000);
	}
	return (FALSE);
}

/*
** -- COREWAR VM MAIN
*/

int				main(int argc, char **argv)
{
	t_cwvm		vm;
	uint8_t		ret;

	if (argc == 1 || ft_strequ(argv[1], "-h"))
		return (err_msg(CW_USAGE));
	if (init_vm(argc, argv, &vm) != SUCCESS)
		return (err_msg(CWE_HELP));
	if (load_players(&vm) == FAILURE)
	{
		ft_putstr_fd(CWE_MALLOC, STDERR_FILENO);
		return (FAILURE);
	}
	if (init_data(&vm) == FAILURE)
		return (del_env(&vm, &vm.ctrl, &vm.jobs));
	ret = run_cpu(&vm, &vm.cpu, &vm.game, &vm.jobs);
	end_game(&vm, &vm.ctrl, &vm.jobs, ret);
	return (SUCCESS);
}
