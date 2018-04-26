/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_verbose.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 02:41:18 by upopee            #+#    #+#             */
/*   Updated: 2018/04/27 01:00:22 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_VERBOSE_H
# define CPU_VERBOSE_H

# define LIV_VERB	(cpu->ctrl->v_level & CWVL_LIVE)
# define V_ALIVE	"Player %hhu (%s) is said to be alive\n"
# define PC_VERB	(cpu->ctrl->v_level & CWVL_PC)
# define V_PCPRINT	"ADV %hhu (0x%.4hx -> 0x%.4hx)"
# define V_CELL		" %.2hhx"

/*
** -- COREWAR VM CPU OPS VERBOSE MESSAGES (ZAZ_VERSION) --
*/

# define V_PC		"%hu"
# define V_RNO		"r%hhu"
# define V_IND		"%hd"
# define V_DIR		"%d"

# define INS_VERB	(cpu->ctrl->v_level & CWVL_INS)
# define IVA		p->pid, p->next_op->name
# define IVPMPT		"P %4u | %s "
# define IVIH(str)	"       | -> " str " " V_DIR " + " V_DIR " = " V_DIR " "
# define IVIM(str)	IVIH(str) "(with pc and mod " V_PC ")\n"
# define IVI(str)	IVIH(str) "(with pc " V_PC ")\n"

# define V_LIVE		IVPMPT V_DIR "\n"
# define V_LD		IVPMPT V_DIR " " V_RNO "\n"
# define V_ST		IVPMPT V_RNO " " V_DIR "\n"
# define V_ADD		IVPMPT V_RNO " " V_RNO " " V_RNO "\n"
# define V_SUB		V_ADD
# define V_AND		IVPMPT V_DIR " " V_DIR " " V_RNO"\n"
# define V_OR		V_AND
# define V_XOR		V_AND
# define V_ZJMPOK	IVPMPT V_IND " OK\n"
# define V_ZJMPKO	IVPMPT V_IND " FAILED\n"
# define V_LDI		IVPMPT V_DIR " " V_DIR " " V_RNO "\n" IVIM("load from")
# define V_STI		IVPMPT V_RNO " " V_DIR " " V_DIR "\n" IVIM("store to")
# define V_FORK		IVPMPT V_IND " (" V_PC ")\n"
# define V_LLD		IVPMPT V_DIR " " V_RNO "\n"
# define V_LLDBUG	IVPMPT V_IND " " V_RNO "\n"
# define V_LLDI		IVPMPT V_DIR " " V_DIR " " V_RNO "\n" IVI("load from")
# define V_LFORK	V_FORK
# define V_AFF		"Aff: %c\n"

#endif

// uint32_t	stop;
// t_list		*curr;
// t_process	*p;
// t_vmctrl	*c;
//
// c = &vm->ctrl;
// stop = vm->ctrl.dump_cycles;
// while (j->nb_processes > 0 && ++cpu->tick)
// {
// 	if (cpu->tick == stop && dump_stop(vm, &stop))
// 		return (TRUE);
// 	CYCL_VERB ? ft_printf(V_CYCLE, cpu->tick) : 0;
// 	INF_DEB ? debug_infos(vm, cpu, g, &c->verbose) : 0;
// 	curr = j->p_stack;
// 	while (curr != NULL && (p = (t_process *)curr->content) != NULL)
// 	{
// 		exec_or_wait(cpu, p, vm->players + (p->player_no - 1), g);
// 		PROC_DEB ? debug_processes(vm, j->p_stack, j) : 0;
// 		RUN_SLOW ? usleep(c->sleep_time) : 0;
// 		curr = curr->next;
// 	}
// 	if (cpu->tick >= g->last_check + g->to_die)
// 		check_gstate(vm, g, j, c);
// }
// return (FALSE);
