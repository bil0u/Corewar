/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_verbose.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 02:41:18 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 03:07:42 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_VERBOSE_H
# define CPU_VERBOSE_H

# define INS_VERB		(cpu->ctrl->v_level & CWVL_ARG)

/*
** -- COREWAR VM CPU OPS VERBOSE MESSAGES (ZAZ_VERSION) --
*/

# define V_ALIVE	"Player %d is alive !"
# define V_CYCLE	"It is now cycle %u"
# define V_KILL		"Process %u hasn't lived for %u cycles (CTD %u)"

# define IVA		p->pid, p->next_op->name
# define IVPMPT		"P %4u | %s "
# define IVIM(str)	"       | -> " str " %d + %d = %d (with pc and mod %u)\n"
# define IVI(str)	"       | -> " str " %d + %d = %d (with pc %u)\n"

# define V_LIVE		IVPMPT "%d\n"
# define V_LD		IVPMPT "%hd r%hhu\n"
# define V_ST		IVPMPT "r%hhu %d\n"
# define V_ADD		IVPMPT "r%hhu r%hhu r%hhu\n"
# define V_SUB		V_ADD
# define V_AND		IVPMPT "%d %d r%hhu\n"
# define V_OR		V_AND
# define V_XOR		V_AND
# define V_ZJMPOK	IVPMPT "%hd OK\n"
# define V_ZJMPKO	IVPMPT "%hd FAILED\n"
# define V_LDI		IVPMPT "%d %d r%hhu\n" IVIM("load from")
# define V_STI		IVPMPT "r%hhu %d %d\n" IVIM("store to")
# define V_FORK		IVPMPT "%hd (%u)\n"
# define V_LLD		V_LD
# define V_LLDI		IVPMPT "%d %d r%hhu\n" IVI("load from")
# define V_LFORK	V_FORK
# define V_AFF		"Aff: %c\n"

#endif
