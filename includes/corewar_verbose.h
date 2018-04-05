/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_verbose.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:02:43 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 15:36:14 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VERBOSE_H
# define COREWAR_VERBOSE_H

/*
** - MACROS FOR USAGE'S STYLE
*/

# define OPC(x)		"{cyan}" x "{eoc}"
# define OPG(x)		"{green}" x "{eoc}"
# define OPR(x)		"{red}" x "{eoc}"
# define OPB(x)		"{blue}" x "{eoc}"
# define OPY(x)		"{yellow}" x "{eoc}"
# define OPM(x)		"{magenta}" x "{eoc}"

# define OPT(o)			OPB(o)
# define OPTN(n)		OPY(n)
# define OPTA(a)		OPC(a)
# define OPTS(s)		OPM(s)

# define OPT_N(o)		OPT(o) " " OPTN("N")
# define OPT_A(o, a)	OPT(o) " " OPTA(a)
# define OPT_P(p)		"[[" OPT_N("-n") "] " OPTS(p) "]"

# define OPT_TXT(o, t)	"\t" OPT(o) "\t   > " t "\n"
# define OPTX_TXT(x, t)	"\t" OPT_N(x) "\t   > " t "\n"
# define OPTN_TXT(n, t)	"\t\t     - " OPTN(n) "\t" t "\n"
# define OPTA_TXT(a, t)	"\t" OPTA(a) "    " t "\n"

# define CAT(t)			"\n{red}--- [{eoc} " t " {red}] ---{eoc}\n\n"

/*
** - LINES THAT NEEDS A LOT OF PARTS
*/

# define CWU_L1P1		"{yellow}Usage:{eoc}\t./corewar ["
# define CWU_L1P2		OPT_N("-d") " " OPT_N("-s") " " OPT_N("-v") " | "
# define CWU_L1P3		OPT_A("-V", "--stealth")
# define CWU_L1P4		"] [" OPT("-a") "] [" OPT("-S") "] "
# define CWU_L1P5		OPT_P("./[path_to_p1].cor") " " OPT_P("./...") "\n"

# define CWU_L2P1		"Prints output of op. aff, hidden by default"

# define CWU_L16P1		"Hides the real contents of the memory"

# define CWU_LENDP1		"\n {red}jrobin, {yellow}glictevoux, {green}upopee, "
# define CWU_LENDP2		"{blue}susivagn {magenta}© 2018 @ 42{eoc}\n\n"

/*
** - USAGE THAT WILL BE PRINTED
*/

# define CWU_L1			CWU_L1P1 CWU_L1P2 CWU_L1P3 CWU_L1P4 CWU_L1P5 "\n"
# define CWU_L2			OPT_TXT("-a", CWU_L2P1)
# define CWU_L3			OPT_TXT("-S", "Slow speed at 1 cycle per second")
# define CWU_L4			CAT("CLASSIC")
# define CWU_L5			OPTX_TXT("-d", "Dumps memory after N cycles then exits")
# define CWU_L6			OPTX_TXT("-s", "Runs N cycles, dumps, pauses, repeat")
# define CWU_L7			OPTX_TXT("-S", "Runs cycles slowly")
# define CWU_L8			OPTX_TXT("-v", "Verbosity level, bitwise | inclusive")
# define CWU_L9			OPTN_TXT("0", "Show only essentials")
# define CWU_L10		OPTN_TXT("1", "Show lives")
# define CWU_L11		OPTN_TXT("2", "Show cycles")
# define CWU_L12		OPTN_TXT("4", "Show operations Args are NOT litteral")
# define CWU_L13		OPTN_TXT("8", "Show deaths")
# define CWU_L14		OPTN_TXT("16", "Show PC movements")
# define CWU_L15		OPTN_TXT("32", "{green}Full debug windowed mode{eoc}")
# define CWU_L16		CAT("VISUALIZER")
# define CWU_L17		OPT_TXT("-V", "SDL output mode")
# define CWU_L18		OPTA_TXT("--stealth", CWU_L16P1)
# define CWU_L19		OPTA_TXT("--mute", "Disable sounds")
# define CWU_LEND		CWU_LENDP1 CWU_LENDP2

# define CW_USAGE1		CWU_L1 CWU_L2 CWU_L3 CWU_L4 CWU_L5 CWU_L6 CWU_L7 CWU_L8
# define CW_USAGE2		CWU_L9 CWU_L10 CWU_L11 CWU_L12 CWU_L13 CWU_L14 CWU_L15
# define CW_USAGE3		CWU_L16 CWU_L17 CWU_L18 CWU_LEND
# define CW_USAGE		CW_USAGE1 CW_USAGE2 CW_USAGE3

# define CWE_NUMERIC	"Please provide a numeric value for '{cyan}%s{eoc}'\n"
# define CWE_OPTARG		"Option '{cyan}%s{eoc}' > {yellow}%s{eoc}"
# define CWE_NOTNUM		CWE_OPTARG " is not a numeric value\n"
# define CWE_SIGN		CWE_OPTARG " remove {green}%c{eoc} sign\n"
# define CWE_OPEN		"Could not open '{yellow}%s{eoc}' file\n"
# define CWE_FILEKO		"'{yellow}%s{eoc}' : invalid binary file\n"
# define CWE_NOFILE		"Missing binary file\n"
# define CWE_BADPNO1	" Option '{cyan}-n{eoc}' > {yellow}%d{eoc} "
# define CWE_BADPNO		CWE_BADPNO1 "Bad player number\n"
# define CWE_PNOUSED	CWE_BADPNO1 "Player number already used\n"
# define CWE_BADOPT		"Option '{yellow}%s{eoc}' is invalid\n"

#endif
