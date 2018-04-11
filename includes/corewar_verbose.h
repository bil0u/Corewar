/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_verbose.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:02:43 by upopee            #+#    #+#             */
/*   Updated: 2018/04/11 22:09:57 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VERBOSE_H
# define COREWAR_VERBOSE_H

/*
** - MACROS FOR USAGE'S STYLE
*/

# define COLD(str)		"{default}" str "{eoc}"
# define COLBK(str)		"{black}" str "{eoc}"
# define COLW(str)		"{white}" str "{eoc}"
# define COLR(str)		"{red}" str "{eoc}"
# define COLG(str)		"{green}" str "{eoc}"
# define COLY(str)		"{yellow}" str "{eoc}"
# define COLB(str)		"{blue}" str "{eoc}"
# define COLM(str)		"{magenta}" str "{eoc}"
# define COLC(str)		"{cyan}" str "{eoc}"

# define OPT(o)			COLB(o)
# define OPTN(n)		COLY(n)
# define OPTA(a)		COLC(a)
# define OPTS(s)		COLM(s)

# define OPT_N(o)		OPT(o) " " OPTN("N")
# define OPT_A(o, a)	OPT(o) " " OPTA(a)
# define OPT_P(p)		"[[" OPT_N("-n") "] " OPTS(p) "]"

# define OPT_TXT(o, t)	"\t" OPT(o) "\t   > " t "\n"
# define OPTX_TXT(x, t)	"\t" OPT_N(x) "\t   > " t "\n"
# define OPTN_TXT(n, t)	"\t\t     - " OPTN(n) "\t" t "\n"
# define OPTA_TXT(a, t)	"\t" OPTA(a) "    " t "\n"

# define CAT(t)			"\n{red}  >>>{eoc} " t " {red}<<<{eoc}\n\n"

/*
** - LINES THAT NEEDS A LOT OF PARTS
*/

# define CWU_L1P1		"{yellow}Usage:{eoc}\t./corewar  ["
# define CWU_L1P2		OPT("-a") "] [" OPT_N("-S") "] [" OPT_N("-v") "]   ["
# define CWU_L1P3		OPT_N("-d") " " OPT_N("-s") " | "
# define CWU_L1P4		OPT_A("-V", "--stealth --mute")
# define CWU_L1P5		 "]   " OPT_P("file.cor ...")

# define CWU_L2P1		"Prints output of op. aff, hidden by default"

# define CWU_L17P1		"Hides the real contents of the memory"

# define CWU_LENDP1		"\n {red}jrobin, {yellow}glictevoux, {green}upopee, "
# define CWU_LENDP2		"{blue}susivagn {magenta}© 2018 @ 42{eoc}\n\n"

/*
** - USAGE THAT WILL BE PRINTED
*/

# define CWU_L1			CWU_L1P1 CWU_L1P2 CWU_L1P3 CWU_L1P4 CWU_L1P5 "\n\n"
# define CWU_L2			CAT("GENERAL OPTIONS")
# define CWU_L3			OPT_TXT("-a", CWU_L2P1)
# define CWU_L4			OPTX_TXT("-S", "Set speed limit at N cycles/seconds")
# define CWU_L5			OPTX_TXT("-v", "Verbosity level, bitwise | inclusive")
# define CWU_L6			OPTN_TXT("0", "Show only essentials (default)")
# define CWU_L7			OPTN_TXT("1", "Show lives")
# define CWU_L8			OPTN_TXT("2", "Show cycles")
# define CWU_L9			OPTN_TXT("4", "Show operations Args are NOT litteral")
# define CWU_L10		OPTN_TXT("8", "Show deaths")
# define CWU_L11		OPTN_TXT("16", "Show PC movements")
# define CWU_L12		OPTN_TXT("32", "{green}Full debug windowed mode{eoc}")
# define CWU_L13		CAT("DUMP MODE")
# define CWU_L14		OPTX_TXT("-d", "Dumps memory after N cycles then exits")
# define CWU_L15		OPTX_TXT("-s", "Runs N cycles, dumps, pauses, repeat")
# define CWU_L16		CAT("VISUALIZER")
# define CWU_L17		OPT_TXT("-V", "SDL output mode")
# define CWU_L18		OPTA_TXT("--stealth", CWU_L17P1)
# define CWU_L19		OPTA_TXT("--mute", "   Disable sounds")
# define CWU_LEND		CWU_LENDP1 CWU_LENDP2

# define CW_USAGE1		CWU_L1 CWU_L2 CWU_L3 CWU_L4 CWU_L5 CWU_L6 CWU_L7 CWU_L8
# define CW_USAGE2		CWU_L9 CWU_L10 CWU_L11 CWU_L12 CWU_L13 CWU_L14 CWU_L15
# define CW_USAGE3		CWU_L16 CWU_L17 CWU_L18 CWU_L19 CWU_LEND
# define CW_USAGE		CW_USAGE1 CW_USAGE2 CW_USAGE3

/*
** - CLASSIC OUTPUT & ERROR MESSAGES
*/

# define CW_SEPR		COLR("-------------------------------------\n")
# define CW_SEPB		COLB("----------------------------------------------\n")
# define CW_SEPG		COLG("-------------------------------------\n")

# define CW_LOADING		COLY(">>> ") "Introducing contestants ...\n" CW_SEPR

# define CW_PLAYERP1	COLY("* ") "Player " COLC("%hhu") ", weighing "
# define CW_PLAYERP2	COLM("%u") " bytes, known as '" COLG("%s") "'\n"
# define CW_PLAYERP3	COLB("* He's saying *") "\n%s\n"
# define CW_PLAYER		CW_PLAYERP1 CW_PLAYERP2 CW_PLAYERP3 CW_SEPR

# define CW_STOP_MSG	COLG(" >> ") "Memory at cycle " COLY("%u")
# define CW_DUMP_MSG	", exiting\n\n"
# define CW_SDMP_MSG	", continuing in 3 secs.\n"
# define CW_SDMPH		CW_SEPB CW_STOP_MSG CW_SDMP_MSG CW_SEPB
# define CW_DUMPH		CW_STOP_MSG CW_DUMP_MSG

# define CW_WIN_MSG1	COLY(">>> ") "Contestant " COLC("%hhu") " aka '"
# define CW_WIN_MSG2	COLG("%s") "' has won !"
# define CW_WINNER_IS	CW_SEPG CW_WIN_MSG1 CW_WIN_MSG2 "\n" CW_SEPG

# define CWE_HELP		"Type '" COLC("./corewar -h") "' to see the usage\n"
# define CWE_NUMERIC	"Please provide a numeric value for '" COLC("%s") "'\n"
# define CWE_OPTARG		"Option '" COLC("%s") "' > " COLY("%s")
# define CWE_NOTNUM		CWE_OPTARG " is not a numeric value\n"
# define CWE_SIGN		CWE_OPTARG " remove " COLG("%c") " sign\n"
# define CWE_UNKNOWN	"'" COLY("%s") "' ; file or option does not exists\n"
# define CWE_FILEKO		"'" COLY("%s") "' : invalid binary file\n"
# define CWE_NOFILE		"Missing binary file\n"
# define CWE_BADPNO1	" Option '" COLC("-n") "' > " COLY("%d")
# define CWE_BADPNO		CWE_BADPNO1 "Bad player number\n"
# define CWE_PNOUSED	CWE_BADPNO1 "Player number already used\n"
# define CWE_BADOPT		"Option '" COLY("%s") "' is invalid\n"
# define CWE_NOPLAYERS	"No .cor files given\n"
# define CWE_BADVERB	"%hu > invalid verbose level\n"

/*
** - DBUG STYLE
*/

# define BPL			32
# define MEM_VALUE		COLB	("   ") COLY("0x%4.4x") " : "
# define MEMSET_COLOR	COLC("%2.2hhx")
# define MEMZERO_COLOR	COLW("%2.2hhx")

# define PCCOLOR_P1		"{black}{b_green}%2.2hhx{eoc}"
# define PCCOLOR_P2		"{white}{b_blue}%2.2hhx{eoc}"
# define PCCOLOR_P3		"{black}{b_yellow}%2.2hhx{eoc}"
# define PCCOLOR_P4		"{white}{b_red}%2.2hhx{eoc}"

# define REGSET_COLOR	COLY("%8.8x")
# define REGZERO_COLOR	COLW("%8.8x")

# define SEPC			COLB("+")
# define SEPH			COLB("|")
# define SEP2			COLB("-")
# define SEPL			COLB("--------") SEPC
# define REG_BEGL1	 	"\n" "   " SEPC
# define REG_BEGL2		"\n" "   " SEPH
# define REGNO_FSZ		COLM("R") SEP2 COLM("%2.2d")
# define REGN			COLB("--") REGNO_FSZ COLB("--") SEPC

# define MEM_HEADER1	"\tCycle " COLY("%u\t")
# define MEM_HEADER		COLG(">> MEMORY <<") MEM_HEADER1 "\n\n"
# define MEM_FOOTER1	"\n" SEPH " Cycles to die " COLY("%u ") SEPH
# define MEM_FOOTER2	" Last check " COLY("%u ") SEPH
# define MEM_FOOTER3	" Max checks " COLY("%u ") SEPH
# define MEM_FOOTER4	" Nb processes " COLG	("%u ") SEPH
# define MEM_FOOTER		MEM_FOOTER1 MEM_FOOTER2 MEM_FOOTER3 MEM_FOOTER4

# define REGHEAD1		"\t PID " COLY("%-4u") " <> Player " COLY("%u ")
# define REGHEAD2		SEPH " Carry " COLY("%u ") SEPH
# define REGHEAD3		" Pending > " COLG("%-6s") " - Timer " COLY("%4u")
# define REG_HEADER		COLG(">> REGISTERS <<") REGHEAD1 REGHEAD2 REGHEAD3 "\n"

#endif
