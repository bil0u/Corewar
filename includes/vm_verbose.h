/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_verbose.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:02:43 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 03:07:29 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VERBOSE_H
# define VM_VERBOSE_H

/*
** -- SEPARATORS --
*/

# define SEPL1			"+---------------------------+----------------------+"
# define SEPL2			"-------------------------------------"
# define SEPB			COLB(SEPL1) "\n"
# define SEPR			COLR(SEPL2) "\n"
# define SEPG			COLG(SEPL2) "\n"

/*
** -- COREWAR VM GAME INTRO & OUTRO --
*/

# define CW_LOADING		COLY(">>> ") "Introducing competitors ...\n" SEPR

# define CW_PLAYERP1	COLY("* ") "Player " COLC("%hhu") ", weighing "
# define CW_PLAYERP2	COLM("%u") " bytes, known as '" COLG("%s") "'\n"
# define CW_PLAYERP3	COLB("* He's saying *") "\n%s\n"
# define CW_PLAYER		CW_PLAYERP1 CW_PLAYERP2 CW_PLAYERP3 SEPR

# define CW_WIN_MSG1	COLY(">>> ") "Competitor " COLC("%hhu") " aka '"
# define CW_WIN_MSG2	COLG("%s") "' has won !"
# define CW_WINNER_IS	SEPG CW_WIN_MSG1 CW_WIN_MSG2 "\n" SEPG

/*
** -- COREWAR VM DUMP & SDUMP HEADERS --
*/

# define CW_STOP_MSG	COLG(" >> ") "Memory at cycle " COLY("%-6u") COLB(" | ")
# define CW_DUMP_MSG	"Exiting\n\n"
# define CW_SDMP_MSG	"Paused for 3 seconds" COLB(" |") "\n"
# define CW_SDMPH		SEPB COLB("|") CW_STOP_MSG CW_SDMP_MSG SEPB
# define CW_DUMPH		CW_STOP_MSG CW_DUMP_MSG

/*
** -- COREWAR VM USAGE STYLE --
*/

# define OPT(o)			COLB(o)
# define OPTN(n)		COLY(n)
# define OPTA(a)		COLC(a)
# define OPTS(s)		COLM(s)

# define OPT_N(o)		OPT(o) " " OPTN("N")
# define OPT_A(o, a)	OPT(o) " " OPTA(a)
# define OPT_P(p)		"[[" OPT_N("-n") "] " OPTS(p) "]"

# define OPT_TXT(o, t)	"\t" OPT(o) "\t   > " t "\n"
# define OPTX_TXT(x, t)	"\t" OPT_N(x) "\t   > " t "\n"
# define OPTN_TXT(n, t)	"\t\t     " OPTN(n) "   " t "\n"
# define OPTA_TXT(a, t)	"\t" OPTA(a) "    " t "\n"

# define CAT(t)			"\n" COLR("  >>> ") t COLR("  <<< ") "\n\n"

/*
** -- COREWAR VM USAGE --
*/

# define CWU_L1P1		COLY("Usage:") "\t./corewar  [" OPT("-a") "] ["
# define CWU_L1P2		OPT_N("-S") "] [" OPT_N("-v") "] [" OPT_N("-D")
# define CWU_L1P3		"]   [" OPT_N("-d") " " OPT_N("-s") " | "
# define CWU_L1P4		OPT_A("-V", "--stealth --mute")
# define CWU_L1P5		 "]   " OPT_P("file.cor ...")
# define CWU_L1			CWU_L1P1 CWU_L1P2 CWU_L1P3 CWU_L1P4 CWU_L1P5 "\n"

# define CWU_L2			CAT("GENERAL OPTIONS")

# define CWU_L3P1		"Prints output of op. aff, hidden by default"
# define CWU_L3			OPT_TXT("-a", CWU_L3P1)
# define CWU_L4			OPTX_TXT("-S", "Set speed limit at N cycles/seconds")
# define CWU_L5			OPTX_TXT("-v", "Verbosity level, bitwise | inclusive")
# define CWU_L6			OPTN_TXT(" 0", "Show only essentials (default)")
# define CWU_L7			OPTN_TXT(" 1", "Show lives")
# define CWU_L8			OPTN_TXT(" 2", "Show cycles")
# define CWU_L9			OPTN_TXT(" 4", "Show operations Args are NOT litteral")
# define CWU_L10		OPTN_TXT(" 8", "Show deaths")
# define CWU_L11		OPTN_TXT("16", "Show PC movements")
# define CWU_L13		OPTX_TXT("-D", "Debug level, bitwise | inclusive.")
# define CWU_L14P1		COLY("    ``/!\\ CAUTION /!\\ ")
# define CWU_L14P2		COLR("This mode slows the program a LOT")
# define CWU_L14		OPTA_TXT("     ", CWU_L14P1 CWU_L14P2)
# define CWU_L15		OPTN_TXT(" 1", "Show game informations")
# define CWU_L16		OPTN_TXT(" 2", "Show the arena memory zone")
# define CWU_L17		OPTN_TXT(" 4", "Show instructions history")
# define CWU_L18		OPTN_TXT(" 8", "Show instructions details")
# define CWU_L19		OPTN_TXT("16", "Show processes details & registers")

# define CWU_L20		CAT("DUMP MODE")
# define CWU_L21		OPTX_TXT("-d", "Dumps memory after N cycles then exits")
# define CWU_L22		OPTX_TXT("-s", "Runs N cycles, dumps, pauses, repeat")

# define CWU_L23		CAT("VISUALIZER")
# define CWU_L24		OPT_TXT("-V", "SDL output mode")
# define CWU_L25P1		"Hides the real contents of the memory"
# define CWU_L25		OPTA_TXT("--stealth", CWU_L25P1)
# define CWU_L26		OPTA_TXT("--mute", "   Disable sounds")

# define CWU_LEND1		"\n {red}jrobin, {yellow}glictevoux, {green}upopee, "
# define CWU_LEND2		"{blue}susivagn {magenta}© 2018 @ 42{eoc}\n\n"
# define CWU_LEND		CWU_LEND1 CWU_LEND2

# define CW_USAGE1		CWU_L1 CWU_L2 CWU_L3 CWU_L4 CWU_L5 CWU_L6 CWU_L7 CWU_L8
# define CW_USAGE2		CWU_L9 CWU_L10 CWU_L11 CWU_L13 CWU_L14 CWU_L15
# define CW_USAGE3		CWU_L16 CWU_L17 CWU_L18 CWU_L19 CWU_L20 CWU_L21 CWU_L22
# define CW_USAGE4		CWU_L23 CWU_L24 CWU_L25 CWU_L26 CWU_LEND
# define CW_USAGE		CW_USAGE1 CW_USAGE2 CW_USAGE3 CW_USAGE4

/*
** -- COREWAR VM ERROR MESSAGES --
*/

# define CWE_HELP		"Type '" COLC("./corewar -h") "' to see the usage\n"
# define CWE_NUMERIC	"Please provide a numeric value for '" COLC("%s") "'\n"
# define CWE_OPTARG		"Option '" COLC("%s") "' > " COLY("%s")
# define CWE_NOTNUM		CWE_OPTARG " is not a numeric value\n"
# define CWE_SIGN		CWE_OPTARG " remove " COLG("%c") " sign\n"
# define CWE_UNKNOWN	"'" COLY("%s") "' : file or option does not exists\n"
# define CWE_NOFILE		"No file after '" COLC("%s") COLC(" %s") "'\n"
# define CWE_NOTFILE	"'" COLY("%s") "' : not a file\n"
# define CWE_FILEKO		"'" COLY("%s") "' : invalid binary file\n"
# define CWE_BADPNO1	" Option '" COLC("-n") "' > " COLY("%d")
# define CWE_BADPNO		CWE_BADPNO1 " Bad player number\n"
# define CWE_PNOUSED	CWE_BADPNO1 " Player number already used\n"
# define CWE_BADOPT		"Option '" COLY("%s") "' is invalid\n"
# define CWE_NOPLAYERS	"No .cor files given\n"
# define CWE_BADVL		COLY("%hu") " > invalid verbose level, maximum is %u\n"
# define CWE_BADDL		COLY("%hu") " > invalid debug level, maximum is %u\n"


#endif
