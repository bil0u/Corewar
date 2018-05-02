/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 02:41:18 by upopee            #+#    #+#             */
/*   Updated: 2018/05/01 23:50:53 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_DEBUG_H
# define CPU_DEBUG_H

/*
** -- STYLE MACROS --
*/

# define REGCOL(s)	COLM(s)
# define INDCOL(s)	COLC(s)
# define DIRCOL(s)	COLY(s)
# define NUMCOL(s)	COLY(s)

# define OKCOL(s)	COLG(s)
# define KOCOL(s)	COLR(s)

# define D_SEP1		"------------------------"
# define D_SEP		COLB(D_SEP1 D_SEP1) "\n"
# define D_SV		" " COLBBK(" ") " "

# define D_RNO		REGCOL("R%hhu")
# define D_IND		INDCOL("%+hd")
# define D_DIR		DIRCOL("0x%.8x")
# define D_NUM		NUMCOL("%+d")
# define D_PC		COLM("PC %hu")
# define D_PCNMOD	"PC" D_IND " = " D_PC
# define D_PCMOD	"PC" D_IND " [%%] = " D_PC

# define D_CYCLE	COLBBK(" ") COLB(" Cycle ") COLC("%-6d")
# define D_PNO		"%sP%hhu{eoc}"
# define D_PID		COLC("ID ") COLY("%hu")
# define D_PIDS		COLC("ID ") COLY("%-7hu")
# define D_PCVAL	COLB("PC ") COLM("%-4u")
# define D_OP		"%-5s"
# define D_ID1		D_CYCLE D_SV D_PCVAL D_SV D_PNO " " D_PIDS D_SV
# define D_IDOK		D_ID1 OKCOL(D_OP) D_SV
# define D_IDKO		D_ID1 KOCOL(D_OP) D_SV
# define D_CARRY	" > Carry set to " COLY("%hhu")

/*
** -- CPU ARGS DEBUG --
*/

# define ARG_DEB	(cpu->ctrl->d_level & CWDL_ARG)
# define ARG_WIN	"arg"
# define ADW		ARG_WIN, 0
# define ADA1		op->name, pending->pc, cpu->ctrl->verbose.color_buff[0],
# define ADA2		pending->player_no, pending->pid, cpu->tick
# define ADA		ADA1 ADA2

# define D_ARG_OPN	COLG("%-5s") COLB(" @ PC ") COLM("%-4u")
# define D_ARG_FROM	COLB(" from ") D_PNO " " D_PIDS
# define D_ARG_ATCY	COLB(" @ Cycle ") COLC("%-4u")
# define D_CURROP	D_ARG_OPN D_ARG_FROM D_ARG_ATCY "\n"

# define D_ARG_PMPT	COLB("#%hhu: ")
# define D_ARG_REG	D_ARG_PMPT REGCOL("[REG]") " > " D_RNO "\n"
# define D_ARG_IND	D_ARG_PMPT INDCOL("[IND]") " > " D_IND "\n"
# define D_IND_MOD	"   %% IDX  > " D_IND "\n"
# define D_ARG_DIR	D_ARG_PMPT DIRCOL("[DIR]") " > " D_DIR "\n"

# define D_CELL		"%.2hhx "
# define D_ARGREAD	COLC("%s") "on " COLY("%hhu") " bytes\n"

/*
** -- CPU INSTRUCTIONS DEBUG --
*/

# define INS_DEB	(cpu->ctrl->d_level & CWDL_INS)
# define INS_WIN	"ins"
# define IDW		INS_WIN, 0
# define IDA1		cpu->tick, p->pc, cpu->ctrl->verbose.color_buff[0],
# define IDA2		p->player_no, p->pid, p->next_op->name
# define IDA		IDA1 IDA2

# define OPBC_OK1	" -> " NUMCOL("%hhu") " args\n"
# define OPBC_OK	"Check " OKCOL("OK") OPBC_OK1
# define OPBC_KO1	" -> Move PC of " NUMCOL("+%hhu") "\n"
# define OPBC_KO	"Check " KOCOL("KO") OPBC_KO1
# define REG_KO		COLB("Arg #%hhu") " > " D_RNO " does not exists\n"

# define D_LIVEPID	"Process %u is alive ! "
# define D_LIVEPL	D_IDOK D_LIVEPID COLG("(Player no.: %hhu)") "\n"
# define D_LIVEPR	D_IDOK D_LIVEPID COLR("(Invalid player no.)") "\n"

# define D_LDIND1	"Loaded " D_DIR " from " D_PCMOD " in "
# define D_LDIND	D_IDOK D_LDIND1 D_RNO D_CARRY "\n"
# define D_LDDIR	D_IDOK "Loaded " D_DIR " in " D_RNO D_CARRY "\n"

# define D_STIND	D_IDOK "Stored " D_DIR " from " D_RNO " at " D_PCMOD "\n"
# define D_STREG	D_IDOK "Stored " D_DIR " from " D_RNO " in " D_RNO "\n"

# define D_MOP(s)	D_RNO " " s " " D_RNO " = " D_NUM " stored in " D_RNO
# define D_ADD		D_IDOK D_MOP("+") D_CARRY "\n"
# define D_SUB		D_IDOK D_MOP("-") D_CARRY "\n"
# define D_BOP(s)	D_DIR " " s " " D_DIR " = " D_NUM " stored in " D_RNO
# define D_AND		D_IDOK D_BOP("&") D_CARRY "\n"
# define D_OR		D_IDOK D_BOP("|") D_CARRY "\n"
# define D_XOR		D_IDOK D_BOP("^") D_CARRY "\n"

# define D_ZJMPOK	D_IDOK "Carry 1 > moving PC of " D_PCMOD "\n"
# define D_ZJMPKO1	"Carry 0 > Jump was " D_IND " but continuing to next op"
# define D_ZJMPKO	D_IDKO D_ZJMPKO1 "\n"

# define D_LDI1		"Loaded " D_DIR " from PC " D_NUM " " D_NUM " [%%] = " D_PC
# define D_LDI		D_IDOK D_LDI1 " in " D_RNO "\n"

# define D_STI1		"Stored " D_DIR " from " D_RNO " at PC " D_NUM " " D_NUM
# define D_STI		D_IDOK D_STI1 " [%%] = " D_PC "\n"

# define D_FORK		D_IDOK "New child " D_PID " set at " D_PCMOD "\n"

# define D_LLDIND1	"Loaded " D_DIR " from " D_PCNMOD " in "
# define D_LLDIND	D_IDOK D_LLDIND1 D_RNO D_CARRY "\n"
# define D_LLDDIR	D_IDOK "Loaded " D_DIR " in " D_RNO D_CARRY "\n"

# define D_LLDI1	"Loaded " D_DIR " from PC " D_NUM " " D_NUM " = " D_PC
# define D_LLDI		D_IDOK D_LLDI1 " in " D_RNO D_CARRY "\n"

# define D_LFORK	D_IDOK "New child " D_PID " set at " D_PCNMOD "\n"

# define D_AFF1		"Printed '" COLY("%c")"' from " D_RNO
# define D_AFF		D_IDOK D_AFF1 "\n"

#endif
