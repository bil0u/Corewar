/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 02:41:18 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 03:07:50 by upopee           ###   ########.fr       */
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
# define IDA			cpu->tick, p->pc, p->player_no, p->pid, p->next_op->name

# define ARG_DEB		(cpu->ctrl->d_level & CWDL_ARG)
# define ARG_WIN		"arg"
# define ADW			ARG_WIN, 0

/*
** -- COREWAR VM CPU OPS VERBOSE STYLE --
*/

# define REGCOL(s)	COLM(s)
# define INDCOL(s)	COLC(s)
# define DIRCOL(s)	COLY(s)
# define NUMCOL(s)	COLY(s)

# define OKCOL(s)	COLG(s)
# define KOCOL(s)	COLR(s)

# define P_OPI		COLB(" PID ") COLY("%-4u") COLB(" CYCLE ") COLC("%-4u") "\n"
# define P_CURROP	COLR("P%hhu: ") COLG("%-5s") COLB(" PC ") COLM("%-4u") P_OPI

# define P_SEP1		"--------------------"
# define P_SEP		COLR(P_SEP1 P_SEP1 P_SEP1) "\n"
# define P_SV		" " COLBBK(" ") " "

# define P_PC		COLM("PC %u")

# define P_RNO		REGCOL("R%hhu")
# define P_IND		INDCOL("%+hd")
# define P_DIR		DIRCOL("0x%.2x")
# define P_NUM		NUMCOL("%+d")

# define P_CYCLE	COLBBK(" ") COLB(" CYCLE ") COLC("%6d")
# define P_PLID		COLR("P%hhu")
# define P_PID		COLB("PID ") COLY("%u")
# define P_PIDS		COLB("PID ") COLY("%5u")
# define P_PCVAL	COLB("PC ") COLM("%4u")
# define P_ID		P_CYCLE P_SV P_PCVAL P_SV P_PLID P_SV P_PIDS P_SV
# define P_OP		"%5s"

# define P_ARG_PMPT	COLB(" #%hhu: ")
# define P_ARG_REG	P_ARG_PMPT REGCOL("[REG]") " > " P_RNO "\n"
# define P_ARG_IND	P_ARG_PMPT INDCOL("[IND]") " > " P_IND "\n"
# define P_IND_MOD	"     %%IDX  > " P_IND "\n"
# define P_ARG_DIR	P_ARG_PMPT DIRCOL("[DIR]") " > " P_DIR "\n"

/*
** -- COREWAR VM CPU OPS VERBOSE MESSAGES --
*/

# define OPBC_OK1	" -> " NUMCOL("%hhu") " args\n"
# define OPBC_OK	"Bytecode " OKCOL("OK") OPBC_OK1
# define OPBC_KO1	" -> Move PC of " NUMCOL("+%hhu") "\n"
# define OPBC_KO	"Bytecode " KOCOL("KO") OPBC_KO1

# define LIVE_OK	P_ID OKCOL(P_OP) P_SV "Player %d is alive !\n"
# define LIVE_KO	P_ID KOCOL(P_OP) P_SV "Player %d does not exist\n"

# define LD_IND		P_ID OKCOL(P_OP) P_SV P_PC " = " P_DIR " >> " P_RNO "\n"
# define LD_DIR		P_ID OKCOL(P_OP) P_SV P_DIR " >> " P_RNO "\n"
# define LD_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define ST_IND		P_ID OKCOL(P_OP) P_SV P_RNO " = " P_DIR " >> " P_PC "\n"
# define ST_REG		P_ID OKCOL(P_OP) P_SV P_RNO " = " P_DIR " >> " P_RNO "\n"
# define ST_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define ADD_OK1	OKCOL(P_OP) P_SV P_RNO " + " P_RNO " = " P_NUM
# define ADD_OK		P_ID ADD_OK1 " >> " P_RNO "\n"
# define ADD_KO		P_ID KOCOL(P_OP) P_SV "One of the parameters is invalid\n"

# define SUB_OK1	OKCOL(P_OP) P_SV P_RNO " - " P_RNO " = " P_NUM
# define SUB_OK		P_ID SUB_OK1 " >> " P_RNO "\n"
# define SUB_KO		P_ID KOCOL(P_OP) P_SV "One of the parameters is invalid\n"

# define AND_OK1	OKCOL(P_OP) P_SV P_DIR " & " P_DIR " = " P_DIR
# define AND_OK		P_ID AND_OK1 " >> " P_RNO "\n"
# define AND_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define OR_OK1		OKCOL(P_OP) P_SV P_DIR " | " P_DIR " = " P_DIR
# define OR_OK		P_ID OR_OK1 " >> " P_RNO "\n"
# define OR_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define XOR_OK1	OKCOL(P_OP) P_SV P_DIR " ^ " P_DIR " = " P_DIR
# define XOR_OK		P_ID XOR_OK1 " >> " P_RNO "\n"
# define XOR_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define ZJMP_OK1	OKCOL(P_OP) P_SV "Carry 1 > moving PC of " P_IND
# define ZJMP_OK	P_ID ZJMP_OK1 " >> " P_PC "\n"
# define ZJMP_KO1	KOCOL(P_OP) P_SV "Carry 0 > Jump was " P_IND
# define ZJMP_KO	P_ID ZJMP_KO1 " but continuing to next op\n"

# define LDI_OK1	OKCOL(P_OP) P_SV P_IND " + " P_IND " <-> " P_PC
# define LDI_OK		P_ID LDI_OK1 " >> " P_RNO " = " P_DIR "\n"
# define LDI_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define STI_OK1	OKCOL(P_OP) P_SV P_RNO " >> " P_IND " + " P_IND
# define STI_OK		P_ID STI_OK1 " <-> " P_PC " = " P_DIR "\n"
# define STI_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define FORK_OK1	OKCOL(P_OP) P_SV "Child > " P_PID " set at PC"
# define FORK_OK	P_ID FORK_OK1 " " P_IND " >> " P_PC "\n"

# define LLD_IND	P_ID OKCOL(P_OP) P_SV P_PC " >> " P_RNO " = " P_DIR "\n"
# define LLD_DIR	P_ID OKCOL(P_OP) P_SV P_DIR " >> " P_RNO "\n"
# define LLD_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define LLDI_OK1	OKCOL(P_OP) P_SV P_IND " + " P_IND " <-> " P_PC
# define LLDI_OK	P_ID LLDI_OK1 " >> " P_RNO " = " P_DIR "\n"
# define LLDI_KO	P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

# define LFORK_OK1	OKCOL(P_OP) P_SV "Child > " P_PID " set at PC"
# define LFORK_OK	P_ID LFORK_OK1 " " P_IND " >> " P_PC "\n"

# define AFF_OK1	OKCOL(P_OP) P_SV "Printed '{yellow}%c{eoc}' <> " P_RNO
# define AFF_OK		P_ID AFF_OK1 "\n"
# define AFF_KO		P_ID KOCOL(P_OP) P_SV P_RNO " does not exists\n"

#endif
