/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_verbose.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:28:30 by upopee            #+#    #+#             */
/*   Updated: 2018/03/22 17:27:46 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_VERBOSE_H
# define CPU_VERBOSE_H

# define P_OPNAME	"{yellow}%s:{eoc}\n"
# define P_RNO		"{yellow}R%hhu{eoc}"
# define P_PC		"(PC{cyan}%+hd{eoc}: {yellow}%u{eoc})"
# define P_HEX		"[{yellow}0x%.2x{eoc}]"
# define P_INT		"[{yellow}%+d{eoc}]"
# define P_HEX_INT	P_HEX " <-> " P_INT

# define P_ARG_OK	"{green}Args bytecode valid, fetching %hhu args{eoc}\n"
# define P_ARG_KO	"{red}Bytecode is invalid, PC >> {yellow}+%hhd{eoc}\n"
# define P_ARG_REG	"{green}Arg %hhu:{eoc} [REGISTER] | " P_HEX "\n"
# define P_ARG_IND	"{green}Arg %hhu:{eoc} [INDIRECT] | " P_HEX "\n"
# define P_ARG_DIR	"{green}Arg %hhu:{eoc} [DIRECT] | " P_HEX "\n"

# define OP_LIVE_OK	"{green}LIVE:{eoc} Player %u is alive !\n"
# define OP_LIVE_KO	"{red}LIVE:{eoc} Player no %u does not exist\n"

# define OP_LD_IND	"{green}LOAD:{eoc} " P_PC " >> " P_RNO "\t" P_HEX "\n"
# define OP_LD_DIR	"{green}LOAD:{eoc} " P_HEX " >> " P_RNO "\n"
# define OP_LD_KO	"{red}LOAD:{eoc} " P_RNO " does not exists\n"

# define OP_ST_IND	"{green}STORE:{eoc} " P_RNO " >> " P_PC "\t" P_HEX "\n"
# define OP_ST_REG	"{green}STORE:{eoc} " P_RNO " >> " P_RNO "\t" P_HEX "\n"
# define OP_ST_KO	"{red}STORE:{eoc} " P_RNO " does not exists\n"

# define OP_ADD_OK1	"{green}ADD:{eoc} " P_RNO " + " P_RNO " >> " P_RNO
# define OP_ADD_OK	OP_ADD_OK1 "\t" P_HEX_INT "\n"
# define OP_ADD_KO	"{red}ADD:{eoc} One of the three parameters is invalid\n"

# define OP_SUB_OK1	"{green}SUB:{eoc} " P_RNO " - " P_RNO " >> " P_RNO
# define OP_SUB_OK	OP_SUB_OK1 "\t" P_HEX_INT "\n"
# define OP_SUB_KO	"{red}SUB:{eoc} One of the three parameters is invalid\n"

# define OP_AND_OK1	"{green}AND:{eoc} " P_HEX " & " P_HEX " >> " P_RNO
# define OP_AND_OK	OP_AND_OK1 "\t" P_HEX "\n"
# define OP_AND_KO	"{red}AND:{eoc} " P_RNO " does not exists\n"

# define OP_OR_OK1	"{green}OR:{eoc} " P_HEX " | " P_HEX " >> " P_RNO
# define OP_OR_OK	OP_OR_OK1 "\t" P_HEX "\n"
# define OP_OR_KO	"{red}OR:{eoc} " P_RNO " does not exists\n"

# define OP_XOR_OK1	"{green}XOR:{eoc} " P_HEX " ^ " P_HEX " >> " P_RNO
# define OP_XOR_OK	OP_XOR_OK1 "\t" P_HEX "\n"
# define OP_XOR_KO	"{red}XOR:{eoc} " P_RNO " does not exists\n"

# define OP_ZJMP_OK	"{green}ZJUMP:{eoc} [Carry = 1] moving PC at " P_INT "\n"
# define OP_ZJMP_KO "{red}ZJUMP:{eoc} [Carry = 0] continuing to next op\n"

# define OP_LDI_KO	"{red}LDI:{eoc} " P_RNO " does not exists\n"

#endif
