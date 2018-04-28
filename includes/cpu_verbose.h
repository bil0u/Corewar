/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_verbose.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 02:41:18 by upopee            #+#    #+#             */
/*   Updated: 2018/04/28 22:07:30 by upopee           ###   ########.fr       */
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

# define V_PC		"%u"
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
