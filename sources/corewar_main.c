/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 16:36:49 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vcpu_types.h"
#include "corewar_types.h"
#include "vcpu.h"
#include "corewar.h"
#include "load_verbose.h"
#include "corewar_verbose.h"

/*
** -- INITIALIZE THE MAIN ENVIRONMENT AND THE LOG WINDOWS
*/

static int	init_vm(int argc, char **argv, t_cwvm *vm)
{
	ft_bzero(vm, sizeof(*vm));
	if (check_argv(argc, argv, vm) != SUCCESS)
		return (FAILURE);
	// new_logwindow("chp", WF_KEEP | WF_CLOSE);
	return (SUCCESS);
}

/*
** -- INITIALIZE THE NEEDED ELEMENTS FOR LAUNCHING THE GAME
*/

static void	init_data(t_cwvm *vm)
{
	t_vmctrl	*ctrl;
	t_jobctrl	*jobs;
	t_gamectrl	*game;
	uint8_t		ret;

	ctrl = &vm->ctrl;
	jobs = &vm->jobs;
	game = &vm->game;
	game->to_die = CYCLE_TO_DIE;
	game->winner = vm->p_indexes[vm->nb_players - 1] + 1;
	jobs->nb_processes = jobs->next_pid;
	vm->cpu.memory = vm->arena;
	vm->cpu.jobs = jobs;
	vm->cpu.ctrl = ctrl;
	ctrl->cycles_sec == 0 ? ctrl->cycles_sec = CPS_DEFAULT : (void)0;
	ctrl->sleep_time = 1000000 / (ctrl->cycles_sec * jobs->nb_processes);
	ctrl->verbose.bar_crop = BAR_CROP;
	ret = ft_sprintf(ctrl->verbose.lbreakdown, "{b_black}");
	ft_memset(ctrl->verbose.lbreakdown + ret, ' ', BAR_LEN);
	new_logwindow("inf", WF_KEEP | WF_CLOSE);
	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	// new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);
	print_memory(vm->arena, jobs->p_stack, "mem");
	// print_registers(NULL, NULL, "reg");
	sleep(1);
}

/*
** -- FREE ALLOCATED ELEMENTS AND DECLARE WINNER
*/

static void	end_game(t_cwvm *vm)
{
	char		*name;
	uint8_t		winner;
	int			i;

	print_memory(vm->arena, vm->jobs.p_stack, "mem");
	print_game_infos(vm, &vm->cpu, &vm->game, &vm->ctrl.verbose);
	i = -1;
	winner = vm->game.winner;
	name = NULL;
	while (++i < vm->nb_players)
		if (vm->players[vm->p_indexes[i]].player_no == winner)
		{
			name = vm->players[vm->p_indexes[i]].header.pname;
			break ;
		}
	ft_lstdel(&vm->jobs.p_stack, &ft_delcontent);
	ft_printf(CW_WINNER_IS, winner, name);
	log_this("chp", 0, CW_WINNER_IS, winner, name);
}

/*
** -- RUN THE CPU FOR A SET CYCLES NUMBER OR UNTIL A WINNER IS FOUND,
**    DEPENDING ON GIVEN OPTIONS
*/

// AMELIORER LA FONCTION -> RUN POUR N CYCLES ou les deux if de fin ne sont check que tout les N cycles

static void	run_cpu(t_cwvm *vm, t_vcpu *cpu, t_gamectrl *game, t_jobctrl *jobs)
{
	int32_t		breakpoint;
	t_list		*pending;
	t_process	*p;

	breakpoint = vm->ctrl.dump_cycles;
	while (jobs->nb_processes > 0 && game->to_die > 0)
	{
		++cpu->tick;
		print_game_infos(vm, cpu, &vm->game, &vm->ctrl.verbose);
		if (cpu->tick == game->last_check + game->to_die)
			check_gamestatus(vm);
		pending = jobs->p_stack;
		while (pending != NULL)
		{
			p = (t_process *)pending->content;
			exec_or_wait(cpu, p, vm->players + (p->player_no - 1), game);
			usleep(vm->ctrl.sleep_time);
			pending = pending->next;
		}
		if (cpu->tick == breakpoint && dump_stop(vm, &breakpoint))
			break ;
	}
}

int			main(int argc, char **argv)
{
	t_cwvm		vm;

	if (init_vm(argc, argv, &vm) != SUCCESS)
		return (err_msg(CWE_HELP));
	load_players(&vm);
	init_data(&vm);

	run_cpu(&vm, &vm.cpu, &vm.game, &vm.jobs);

	end_game(&vm);
	return (SUCCESS);
}
