/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vcpu_verbose.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 21:31:20 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 01:20:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VCPU_VERBOSE_H
# define VCPU_VERBOSE_H

/*
** -- COREWAR VM CPU OPS VERBOSE STYLE --
*/

# define REGCOL(s)	COLM(s)
# define INDCOL(s)	COLC(s)
# define DIRCOL(s)	COLY(s)
# define NUMCOL(s)	COLY(s)

# define OKCOL(s)	COLG(s)
# define KOCOL(s)	COLR(s)

# define P_SEP1		"--------------------"
# define P_SEP		COLR(P_SEP1 P_SEP1 P_SEP1) "\n"
# define P_VSEP		" " COLBBK(" ") "  "

# define P_CURR_OP	"> Op " COLM("%d") " '" COLY("%s") "' " COLB("@ PC %u") "\n"
# define P_PC		"(PC: " COLC("%u") " )"

# define P_RNO		REGCOL("R%hhu")
# define P_IND		INDCOL("%+hd")
# define P_DIR		DIRCOL("0x%.2x")
# define P_INT		NUMCOL("%+d")

# define P_PLID		COLR("P%hhu ")
# define P_PID		COLB("PID ") COLY("%-5u")
# define P_CYCLE	COLB("Cycle ") COLC("%-5d")
# define P_ID		P_CYCLE P_VSEP P_PLID P_PID P_VSEP

# define P_ARG_PMPT	COLB(" #%hhu: ")
# define P_ARG_REG	P_ARG_PMPT REGCOL("[REG]") " > " P_RNO "\n"
# define P_ARG_IND	P_ARG_PMPT INDCOL("[IND]") " > " P_IND "\n"
# define P_IND_MOD	"     %%IDX  > " P_IND "\n"
# define P_ARG_DIR	P_ARG_PMPT DIRCOL("[DIR]") " > " P_DIR "\n"

/*
** -- COREWAR VM CPU OPS VERBOSE MESSAGES --
*/

# define OPBC_OK	OKCOL("Bytecode OK") " - fetching " NUMCOL("%hhu") " args\n"
# define OPBC_KO	KOCOL("Bytecode KO") " - PC >> " NUMCOL("+%hhu") "\n"

# define LIVE_OK	P_ID OKCOL("LIVE: ") "Player %u is alive !\n"
# define LIVE_KO	P_ID KOCOL("LIVE: ") "Player %u does not exist\n"

# define LD_IND		P_ID OKCOL("LD: ") P_PC " = " P_DIR " >> " P_RNO "\n"
# define LD_DIR		P_ID OKCOL("LD: ") P_DIR " >> " P_RNO "\n"
# define LD_KO		P_ID KOCOL("LD: ") P_RNO " does not exists\n"

# define ST_IND		P_ID OKCOL("ST: ") P_RNO " = " P_DIR " >> " P_PC "\n"
# define ST_REG		P_ID OKCOL("ST: ") P_RNO " = " P_DIR " >> " P_RNO "\n"
# define ST_KO		P_ID KOCOL("ST: ") P_RNO " does not exists\n"

# define ADD_OK1	OKCOL("ADD: ") P_RNO " + " P_RNO " = " P_INT
# define ADD_OK		P_ID ADD_OK1 " >> " P_RNO "\n"
# define ADD_KO		P_ID KOCOL("ADD: ") "One of the parameters is invalid\n"

# define SUB_OK1	OKCOL("SUB: ") P_RNO " - " P_RNO " = " P_INT
# define SUB_OK		P_ID SUB_OK1 " >> " P_RNO "\n"
# define SUB_KO		P_ID KOCOL("SUB: ") "One of the parameters is invalid\n"

# define AND_OK1	OKCOL("AND: ") P_DIR " & " P_DIR " = " P_DIR
# define AND_OK		P_ID AND_OK1 " >> " P_RNO "\n"
# define AND_KO		P_ID KOCOL("AND: ") P_RNO " does not exists\n"

# define OR_OK1		OKCOL("OR: ") P_DIR " | " P_DIR " = " P_DIR
# define OR_OK		P_ID OR_OK1 " >> " P_RNO "\n"
# define OR_KO		P_ID KOCOL("OR: ") P_RNO " does not exists\n"

# define XOR_OK1	OKCOL("XOR: ") P_DIR " ^ " P_DIR " = " P_DIR
# define XOR_OK		P_ID XOR_OK1 " >> " P_RNO "\n"
# define XOR_KO		P_ID KOCOL("XOR: ") P_RNO " does not exists\n"

# define ZJMP_OK1	OKCOL("ZJMP: ") "[Carry = 1] moving PC of " P_IND
# define ZJMP_OK	P_ID ZJMP_OK1 " >> PC is now at " P_INT "\n"
# define ZJMP_KO	P_ID KOCOL("ZJMP: ") "[Carry = 0] continuing to next op\n"

# define LDI_OK1	OKCOL("LDI: ") P_INT " + " P_INT " <-> " P_PC
# define LDI_OK		P_ID LDI_OK1 " >> " P_RNO " = " P_DIR "\n"
# define LDI_KO		P_ID KOCOL("LDI: ") P_RNO " does not exists\n"

# define STI_OK1	OKCOL("STI: ") P_RNO " >> " P_INT " + " P_INT
# define STI_OK		P_ID STI_OK1 " <-> " P_PC " = " P_DIR "\n"
# define STI_KO		P_ID KOCOL("STI: ") P_RNO " does not exists\n"

# define FORK_OK1	OKCOL("FORK: ") "Child (" P_PID ") set at " P_PC
# define FORK_OK	P_ID FORK_OK1 " " P_IND " >> " P_PC "\n"

# define LLD_IND	P_ID OKCOL("LLD: ") P_PC " >> " P_RNO " = " P_DIR "\n"
# define LLD_DIR	P_ID OKCOL("LLD: ") P_DIR " >> " P_RNO "\n"
# define LLD_KO		P_ID KOCOL("LLD: ") P_RNO " does not exists\n"

# define LLDI_OK1	OKCOL("LLDI: ") P_INT " + " P_INT " <-> " P_PC
# define LLDI_OK	P_ID LLDI_OK1 " >> " P_RNO " = " P_DIR "\n"
# define LLDI_KO	P_ID KOCOL("LLDI: ") P_RNO " does not exists\n"

# define LFORK_OK1	OKCOL("LFORK: ") "Child (" P_PID ") set at " P_PC
# define LFORK_OK	P_ID LFORK_OK1 " " P_IND " >> " P_PC "\n"

# define AFF_OK1	OKCOL("AFF: ") "Printed '{yellow}%c{eoc}' <> " P_RNO
# define AFF_OK		P_ID OKCOL("AFF: ") "Printed '{yellow}%c{eoc}' <> " P_RNO "\n"
# define AFF_KO		P_ID KOCOL("AFF: ") P_RNO " does not exists\n"

#endif
