/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_verbose.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:02:43 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 01:48:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VERBOSE_H
# define COREWAR_VERBOSE_H

/*
** -- SEPARATORS --
*/

# define SEPR			COLR("-------------------------------------\n")
# define SEPB			COLB("----------------------------------------------\n")
# define SEPG			COLG("-------------------------------------\n")

/*
** -- COREWAR VM GAME INTRO & OUTRO --
*/

# define CW_LOADING		COLY(">>> ") "Introducing contestants ...\n" SEPR

# define CW_PLAYERP1	COLY("* ") "Player " COLC("%hhu") ", weighing "
# define CW_PLAYERP2	COLM("%u") " bytes, known as '" COLG("%s") "'\n"
# define CW_PLAYERP3	COLB("* He's saying *") "\n%s\n"
# define CW_PLAYER		CW_PLAYERP1 CW_PLAYERP2 CW_PLAYERP3 SEPR

# define CW_WIN_MSG1	COLY(">>> ") "Contestant " COLC("%hhu") " aka '"
# define CW_WIN_MSG2	COLG("%s") "' has won !"
# define CW_WINNER_IS	SEPG CW_WIN_MSG1 CW_WIN_MSG2 "\n" SEPG

/*
** -- COREWAR VM DUMP & SDUMP HEADERS --
*/

# define CW_STOP_MSG	COLG(" >> ") "Memory at cycle " COLY("%u")
# define CW_DUMP_MSG	", exiting\n\n"
# define CW_SDMP_MSG	", continuing in 3 secs.\n"
# define CW_SDMPH		SEPB CW_STOP_MSG CW_SDMP_MSG SEPB
# define CW_DUMPH		CW_STOP_MSG CW_DUMP_MSG

/*
** -- COREWAR VM INFO STYLE --
*/

# define INF_HEAD		COLG(">> INFO <<\n\n")

# define INF_PSQC		"%s" COLBK(" P%hhu ")
# define INF_NBLIVE		"Lives " COLG("%-3u")

# define INF_M1P1		"   " "Cycle " COLC("%-7d")
# define INF_M1P2		"%15s" "Processes " COLM("%-4u") "   " INF_NBLIVE
# define INF_M1P3		"   " "Last live  " INF_PSQC
# define INF_MSG1		INF_M1P1 INF_M1P2 INF_M1P3 "\n\n"

# define INF_PSTAT1		"    " INF_PSQC "  "
# define INF_PSTAT21	"  " "Childs " COLY("%-4u")
# define INF_PSTAT22	"   " INF_NBLIVE
# define INF_PSTAT23	"   " "Last live  " COLC("%u")
# define INF_PSTAT2		INF_PSTAT21 INF_PSTAT22 INF_PSTAT23 "\n\n"
# define INF_PNAME		"%s%-22s{eoc}"
# define INF_PNAMEL		"%s%-.19s...{eoc}"
# define INF_BUFFSTAT	"%s\n"

# define INF_BAR1		"   " "Current period    >      %s{eoc}\n\n"
# define INF_BAR2		"   " "Last period       >      %s{eoc}\n\n"
# define INF_BARS		INF_BAR1 INF_BAR2

# define INF_SEPV		"  " SEPV "  "
# define INF_M2P1		"\n" "   " "To die " COLY("%4d") INF_SEPV
# define INF_M2P2		COLC("%2u") "/" COLG("%.2u") " Checks" INF_SEPV
# define INF_M2P3		"Last check " COLY("%6d") INF_SEPV
# define INF_M2P4		"Next check in " COLY("%4d")

# define INF_MSG2		INF_M2P1 INF_M2P2 INF_M2P3 INF_M2P4 "\n"

# define INF_MSG		INF_HEAD INF_MSG1 INF_BUFFSTAT INF_BARS INF_MSG2

#endif
