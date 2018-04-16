/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_verbose.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:28:30 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 18:55:49 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_VERBOSE_H
# define CPU_VERBOSE_H

/*
** -- PRINTING STRUCTURE MACROS --
*/

# define P_SEPP		"--------------------"
# define P_SEP		"{red}" P_SEPP P_SEPP P_SEPP "\n{eoc}"
# define P_CURR_OP	"> Op {magenta}%d{eoc} '{yellow}%s{eoc}'{blue} @ PC %u\n"
# define P_RNO		"{cyan}R%hhu{eoc}"
# define P_PC		"(PC: {magenta}%u{eoc})"
# define P_HEX		"{yellow}0x%.2x{eoc}"
# define P_INT		"{magenta}%+d{eoc}"
# define P_IND		"{magenta}%+hd{eoc}"
# define P_PID		"{blue}PID {cyan}%-4u{eoc}"
# define P_CYCLE	"Cycle {yellow}%-5d{eoc}"
# define P_ID		"{yellow}P%hhu{eoc} " P_PID " | " P_CYCLE " | "

# define P_ARG_OK	"{green}Bytecode OK{eoc} - fetching %hhu args\n"
# define P_ARG_KO	"{red}Bytecode KO{eoc} - PC >> {yellow}+%hhd{eoc}\n"
# define P_ARG_PMPT	" {blue}#%hhu:{eoc} "
# define P_ARG_REG	P_ARG_PMPT "[{cyan}REG{eoc}] > " P_RNO "\n"
# define P_ARG_IND	P_ARG_PMPT "[{magenta}IND{eoc}] > " P_IND "\n"
# define P_IND_MOD	"     %%IDX  > " P_IND "\n"
# define P_ARG_DIR	P_ARG_PMPT "[{yellow}DIR{eoc}] > " P_HEX "\n"

/*
** -- INSTRUCTIONS TEXT --
*/

# define LIVE_OK	P_ID "{green}LIVE:{eoc} Player %u is alive !\n"
# define LIVE_KO	P_ID "{red}LIVE:{eoc} Player %u does not exist\n"

# define LD_IND1	"{green}LD:{eoc} " P_PC " = " P_HEX " >> " P_RNO
# define LD_IND		P_ID LD_IND1 "\n"
# define LD_DIR		P_ID "{green}LD:{eoc} " P_HEX " >> " P_RNO "\n"
# define LD_KO		P_ID "{red}LD:{eoc} " P_RNO " does not exists\n"

# define ST_IND1	"{green}ST:{eoc} " P_RNO " = " P_HEX " >> " P_PC
# define ST_IND		P_ID ST_IND1 "\n"
# define ST_REG1	"{green}ST:{eoc} " P_RNO " = " P_HEX " >> " P_RNO
# define ST_REG		P_ID ST_REG1 "\n"
# define ST_KO		P_ID "{red}ST:{eoc} " P_RNO " does not exists\n"

# define ADD_OK1	"{green}ADD:{eoc} " P_RNO " + " P_RNO " = " P_INT
# define ADD_OK		P_ID ADD_OK1 " >> " P_RNO "\n"
# define ADD_KO		P_ID "{red}ADD:{eoc} One of the parameters is invalid\n"

# define SUB_OK1	"{green}SUB:{eoc} " P_RNO " - " P_RNO " = " P_INT
# define SUB_OK		P_ID SUB_OK1 " >> " P_RNO "\n"
# define SUB_KO		P_ID "{red}SUB:{eoc} One of the parameters is invalid\n"

# define AND_OK1	"{green}AND:{eoc} " P_HEX " & " P_HEX " = " P_HEX
# define AND_OK		P_ID AND_OK1 " >> " P_RNO "\n"
# define AND_KO		P_ID "{red}AND:{eoc} " P_RNO " does not exists\n"

# define OR_OK1		"{green}OR:{eoc} " P_HEX " | " P_HEX " = " P_HEX
# define OR_OK		P_ID OR_OK1 " >> " P_RNO "\n"
# define OR_KO		P_ID "{red}OR:{eoc} " P_RNO " does not exists\n"

# define XOR_OK1	"{green}XOR:{eoc} " P_HEX " ^ " P_HEX " = " P_HEX
# define XOR_OK		P_ID XOR_OK1 " >> " P_RNO "\n"
# define XOR_KO		P_ID "{red}XOR:{eoc} " P_RNO " does not exists\n"

# define ZJMP_OK1	"{green}ZJMP:{eoc} [Carry = 1] moving PC of " P_IND
# define ZJMP_OK	P_ID ZJMP_OK1 " >> PC is now at " P_INT "\n"
# define ZJMP_KO	P_ID "{red}ZJMP:{eoc} [Carry = 0] continuing to next op\n"

# define LDI_OK1	"{green}LDI:{eoc} " P_INT " + " P_INT " <-> " P_PC
# define LDI_OK		P_ID LDI_OK1 " >> " P_RNO " = " P_HEX "\n"
# define LDI_KO		P_ID "{red}LDI:{eoc} " P_RNO " does not exists\n"

# define STI_OK1	"{green}STI:{eoc} " P_RNO " >> " P_INT " + " P_INT
# define STI_OK		P_ID STI_OK1 " <-> " P_PC " = " P_HEX "\n"
# define STI_KO		P_ID "{red}STI:{eoc} " P_RNO " does not exists\n"

# define FORK_OK1	"{green}FORK:{eoc} Child (" P_PID ") set at " P_PC
# define FORK_OK	P_ID FORK_OK1 " " P_IND " >> " P_PC "\n"

# define LLD_IND	P_ID "{green}LLD:{eoc} " P_PC " >> " P_RNO " = " P_HEX "\n"
# define LLD_DIR	P_ID "{green}LLD:{eoc} " P_HEX " >> " P_RNO "\n"
# define LLD_KO		P_ID "{red}LLD:{eoc} " P_RNO " does not exists\n"

# define LLDI_OK1	"{green}LLDI:{eoc} " P_INT " + " P_INT " <-> " P_PC
# define LLDI_OK	P_ID LLDI_OK1 " >> " P_RNO " = " P_HEX "\n"
# define LLDI_KO	P_ID "{red}LLDI:{eoc} " P_RNO " does not exists\n"

# define LFORK_OK1	"{green}LFORK:{eoc} Child (" P_PID ") set at " P_PC
# define LFORK_OK	P_ID LFORK_OK1 " " P_IND " >> " P_PC "\n"

# define AFF_OK1	"{green}AFF:{eoc} Printed '{yellow}%c{eoc}' from " P_RNO
# define AFF_OK		P_ID AFF_OK1 "\n"
# define AFF_KO		P_ID "{red}AFF:{eoc} " P_RNO " does not exists\n"

#endif
