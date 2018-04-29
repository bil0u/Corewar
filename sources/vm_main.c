/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/29 04:08:45 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "vm_verbose.h"
#include "vm_debug.h"

/*
** -- FREE ALLOCATED ELEMENTS AND DECLARE WINNER
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
	ft_lstdel(&j->p_stack, &ft_delcontent);
	if (dumped == FALSE)
		ft_printf((c->flags & CWF_VERB ? CW_ZWINNER_IS : CW_WINNER_IS),
			winner, name);
	tcsetattr(STDIN_FILENO, TCSANOW, &v->ctrl.t_save);
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
	while (curr != NULL)
	{
		p = (t_process *)curr->content;
		exec_or_wait(cpu, p, vm->players + (p->player_no - 1), g);
		PROC_DEB ? debug_processes(vm, j->p_stack, j) : 0;
		RUN_SLOW ? usleep(c->sleep_time) : 0;
		curr = curr->next;
	}
}

/*
** -- RUN THE CPU FOR A SET CYCLES NUMBER OR UNTIL A WINNER IS FOUND,
**    DEPENDING ON GIVEN OPTIONS
*/

static int		run_cpu(t_cwvm *vm, t_vcpu *cpu, t_gamectrl *g, t_jobctrl *j)
{
	uint32_t	breakpoint;
	t_vmctrl	*c;
	char		key_input;

	c = &vm->ctrl;
	breakpoint = vm->ctrl.dump_cycles;
	while (j->nb_processes > 0)
	{
		if (read(STDIN_FILENO, &key_input, 1) > 0 && key_input == ' ')
			c->paused = ~(c->paused);
		if (c->paused == 0 || key_input == '\n')
		{
			++cpu->tick;
			key_input = 0;
			CYCL_VERB ? ft_printf(V_CYCLE, cpu->tick) : 0;
			INF_DEB ? debug_infos(vm, cpu, g, &c->verbose) : 0;
			consume_cycle(vm, cpu, g, j);
			if (cpu->tick == breakpoint && dump_stop(vm, &breakpoint) == TRUE)
				return (TRUE);
			if (cpu->tick >= g->last_check + g->to_die)
				check_gstate(vm, g, j, c);
		}
	}
	return (FALSE);
}

int				main(int argc, char **argv)
{
	t_cwvm		vm;
	uint8_t		ret;

	if (argc == 1 || ft_strequ(argv[1], "-h"))
		return (err_msg(CW_USAGE));
	if (init_vm(argc, argv, &vm) != SUCCESS)
		return (err_msg(CWE_HELP));
	if (load_players(&vm) == FAILURE)
		return (err_msg(CWE_MALLOC));
	init_data(&vm);
	ret = run_cpu(&vm, &vm.cpu, &vm.game, &vm.jobs);
	end_game(&vm, &vm.ctrl, &vm.jobs, ret);
	return (SUCCESS);
}
