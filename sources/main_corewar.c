/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 20:27:06 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "cpu.h"
#include "corewar.h"
#include "corewar_verbose.h"

/*
** -- INITIALIZE THE MAIN ENVIRONMENT AND THE LOG WINDOWS
*/

static int	init_vm(int argc, char **argv, t_cwvm *vm)
{
	ft_bzero(vm, sizeof(*vm));
	if (check_argv(argc, argv, vm) != SUCCESS)
		return (FAILURE);
	new_logwindow("inf", WF_KEEP | WF_CLOSE);
	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);
	new_logwindow("chp", WF_KEEP | WF_CLOSE);
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
	vm->cpu.jobs = &vm->jobs;
	vm->cpu.ctrl = &vm->ctrl;
	if (ctrl->flags & CWF_SLOW)
		ctrl->sleep_time = 1000000 / (ctrl->cycles_sec * jobs->nb_processes);
	ret = ft_sprintf(ctrl->verbose.last_breakdown, "{b_black}");
	ft_memset(ctrl->verbose.last_breakdown + ret, ' ', BATTLEBAR_LEN);
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
	i = -1;
	winner = vm->game.winner;
	name = NULL;
	while (++i < vm->nb_players)
		if (vm->players[vm->p_indexes[i]].player_no == winner)
		{
			name = vm->players[vm->p_indexes[i]].header.prog_name;
			break ;
		}
	ft_lstdel(&vm->jobs.p_stack, &ft_delcontent);
	ft_printf(CW_WINNER_IS, winner, name);
	log_this("chp", 0, CW_WINNER_IS, winner, name);
}

static void		p_bar(t_cwvm *vm, t_gamectrl *game, char *bar)
{
	uint8_t		curr_player;
	uint8_t		p_no;
	uint8_t		nb;
	uint8_t		ret;

	curr_player = 0;
	ret = 0;
	while (curr_player < vm->nb_players)
	{
		p_no = vm->p_indexes[curr_player++];
		if (p_no + 1 < 3)
			ret += ft_sprintf(bar + ret, (p_no + 1 == 1 ? BARC_P1 : BARC_P2));
		else
			ret += ft_sprintf(bar + ret, (p_no + 1 == 3 ? BARC_P3 : BARC_P4));
		nb = (vm->players[p_no].nb_lives * BATTLEBAR_LEN) / game->nb_lives;
		ft_memset(bar + ret, ' ', nb);
		ret += nb;
	}
}

static void p_info(t_cwvm *vm, t_vcpu *cpu, t_gamectrl *game, t_jobctrl *jobs)
{
	char			*curr_break;
	char			*last_break;
	uint8_t			ret;

	curr_break = vm->ctrl.verbose.curr_breakdown;
	last_break = vm->ctrl.verbose.last_breakdown;
	if (game->nb_lives == 0)
	{
		ret = ft_sprintf(curr_break, "{b_black}");
		ft_memset(curr_break + ret, ' ', BATTLEBAR_LEN);
	}
	else
		p_bar(vm, game, curr_break);
	clear_window("inf");
	log_this("inf", 0, INF_MSG, cpu->tick, jobs->nb_processes, game->nb_lives,
		game->to_die, game->last_check, game->nb_checks, MAX_CHECKS,
		last_break, curr_break);
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
		p_info(vm, cpu, game, jobs);
		if (cpu->tick == game->last_check + game->to_die)
			check_gamestatus(vm);
		pending = jobs->p_stack;
		while (pending != NULL)
		{
			p = (t_process *)pending->content;
			exec_or_wait(cpu, p, vm->players + (p->player_no - 1), game);
			vm->ctrl.flags & CWF_SLOW ? usleep(vm->ctrl.sleep_time) : (void)0;
			pending = pending->next;
		}
		if (cpu->tick == breakpoint)
			if (dump_stop(vm, &breakpoint) == TRUE)
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
