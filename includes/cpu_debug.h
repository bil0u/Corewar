/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 02:41:18 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 20:50:53 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_DEBUG_H
# define CPU_DEBUG_H

/*
** -- USEFUL MACROS --
*/

# define INS_DEB		(cpu->ctrl->d_level & CWDL_INS)
# define INS_WIN		"ins"
# define IDW			INS_WIN, 0
# define IDA			cpu->tick, p->pc, cpu->ctrl->verbose.color_buff[0], \
						p->player_no, p->pid, p->next_op->name

# define ARG_DEB		(cpu->ctrl->d_level & CWDL_ARG)
# define ARG_WIN		"arg"
# define ADW			ARG_WIN, 0
# define ADA			cpu->ctrl->verbose.color_buff[0], pending->player_no, \
						op->name, pending->pc, pending->pid, cpu->tick

# define MDA			cpu->memory, cpu->jobs->p_stack
/*
** -- COREWAR VM CPU OPS VERBOSE STYLE --
*/

# define REGCOL(s)	COLM(s)
# define INDCOL(s)	COLC(s)
# define DIRCOL(s)	COLY(s)
# define NUMCOL(s)	COLY(s)

# define OKCOL(s)	COLG(s)
# define KOCOL(s)	COLR(s)

# define P_OPI		COLM("%-4u ") P_PIDS COLB(" CYCLE ") COLC("%-4u")
# define P_CURROP	P_PNO COLG(" %-5s") COLB(" PC ") P_OPI "\n"

# define P_SEP1		"--------------------"
# define P_SEP		COLR(P_SEP1 P_SEP1 P_SEP1) "\n"
# define P_SV		" " COLBBK(" ") " "

# define P_RNO		REGCOL("R%hhu")
# define P_IND		INDCOL("%+hd")
# define P_DIR		DIRCOL("0x%.8x")
# define P_NUM		NUMCOL("%+d")
# define P_PC		COLM("PC %hu")
# define P_PCNMOD	"PC" P_IND " = " P_PC
# define P_PCMOD	"PC" P_IND " [%%] = " P_PC

# define P_CYCLE	COLBBK(" ") COLB(" CYCLE ") COLC("%6d")
# define P_PNO		COLR("%sP%hhu{eoc}")
# define P_PID		COLB("PID ") COLY("%hu")
# define P_PIDS		COLB("PID ") COLY("%-3hu")
# define P_PCVAL	COLB("PC ") COLM("%4u")
# define P_OP		"%5s"
# define P_ID1		P_CYCLE P_SV P_PCVAL P_SV P_PNO P_SV P_PIDS P_SV
# define P_IDOK		P_ID1 OKCOL(P_OP) P_SV
# define P_IDKO		P_ID1 KOCOL(P_OP) P_SV
# define P_CARRY	" > Carry set to " COLY("%hhu")

# define P_ARG_PMPT	COLB("#%hhu: ")
# define P_ARG_REG	P_ARG_PMPT REGCOL("[REG]") " > " P_RNO "\n"
# define P_ARG_IND	P_ARG_PMPT INDCOL("[IND]") " > " P_IND "\n"
# define P_IND_MOD	"     %%IDX  > " P_IND "\n"
# define P_ARG_DIR	P_ARG_PMPT DIRCOL("[DIR]") " > " P_DIR "\n"

/*
** -- COREWAR VM CPU OPS VERBOSE MESSAGES --
*/

# define OPBC_OK1	" -> " NUMCOL("%hhu") " args\n"
# define OPBC_OK	"Check " OKCOL("OK") OPBC_OK1
# define OPBC_KO1	" -> Move PC of " NUMCOL("+%hhu") "\n"
# define OPBC_KO	"Check " KOCOL("KO") OPBC_KO1
# define REG_KO		COLB("Arg #%hhu") " > " P_RNO " does not exists\n"

# define D_LIVEOK	P_IDOK "Player %hhu is alive !\n"

# define D_LDIND1	"Loaded " P_DIR " from " P_PCMOD " in "
# define D_LDIND	P_IDOK D_LDIND1 P_RNO P_CARRY "\n"
# define D_LDDIR	P_IDOK "Loaded " P_DIR " in " P_RNO P_CARRY "\n"

# define D_STIND	P_IDOK "Stored " P_DIR " from " P_RNO " at " P_PCMOD "\n"
# define D_STREG	P_IDOK "Stored " P_DIR " from " P_RNO " in " P_RNO "\n"

# define D_MOP(s)	P_RNO " " s " " P_RNO " = " P_NUM " stored in " P_RNO
# define D_ADD		P_IDOK D_MOP("+") P_CARRY "\n"
# define D_SUB		P_IDOK D_MOP("-") P_CARRY "\n"
# define D_BOP(s)	P_DIR " " s " " P_DIR " = " P_NUM " stored in " P_RNO
# define D_AND		P_IDOK D_BOP("&") P_CARRY "\n"
# define D_OR		P_IDOK D_BOP("|") P_CARRY "\n"
# define D_XOR		P_IDOK D_BOP("^") P_CARRY "\n"

# define D_ZJMPOK	P_IDOK "Carry 1 > moving PC of " P_PCMOD "\n"
# define D_ZJMPKO1	"Carry 0 > Jump was " P_IND " but continuing to next op"
# define D_ZJMPKO	P_IDKO D_ZJMPKO1 "\n"

# define D_LDI1		"Loaded " P_DIR " from PC " P_NUM " " P_NUM " [%%] = " P_PC
# define D_LDI		P_IDOK D_LDI1 " in " P_RNO P_CARRY "\n"

# define D_STI1		"Stored " P_DIR " from " P_RNO " at PC " P_NUM " " P_NUM
# define D_STI		P_IDOK D_STI1 " [%%] = " P_PC "\n"

# define D_FORK		P_IDOK "New child " P_PID " set at " P_PCMOD "\n"

# define D_LLDIND1	"Loaded " P_DIR " from " P_PCNMOD " in "
# define D_LLDIND	P_IDOK D_LLDIND1 P_RNO P_CARRY "\n"
# define D_LLDDIR	P_IDOK "Loaded " P_DIR " in " P_RNO P_CARRY "\n"

# define D_LLDI1	"Loaded " P_DIR " from PC " P_NUM " " P_NUM " = " P_PC
# define D_LLDI		P_IDOK D_LLDI1 " in " P_RNO P_CARRY "\n"

# define D_LFORK	P_IDOK "New child " P_PID " set at " P_PCNMOD "\n"

# define D_AFF1		"Printed '" COLY("%c")"' from " P_RNO
# define D_AFF		P_IDOK D_AFF1 "\n"

#endif
