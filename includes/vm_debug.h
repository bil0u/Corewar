/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 02:10:18 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 05:17:14 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_DEBUG_H
# define VM_DEBUG_H

/*
** -- USEFUL MACROS --
*/

# define INF_DEB		(cpu->ctrl->d_level & CWDL_INF)
# define INF_WIN		"inf"
# define MEM_DEB		(cpu->ctrl->d_level & CWDL_MEM)
# define MEM_WIN		"mem"
# define REG_DEB		(cpu->ctrl->d_level & CWDL_REG)
# define REG_WIN		"reg"

/*
** -- VM INFO STYLE --
*/

# define INF_HEAD		COLG(">> INFO <<\n\n")

# define INF_PSQC		"%s" COLBK(" P%hhu ")
# define INF_NBLIVE		"Lives " COLG("%-3u")

# define INF_M1P1		"   " "Cycle " COLC("%-6d")
# define INF_M1P2		"%16s" "Processes " COLM("%-4u") "   " INF_NBLIVE
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

# define INF_BARMSG		"                          " "%s%50s\n\n"
# define COMMENT_NOONE	" {eoc}Nobody seems to be alive ... " COLM("PUSSIES !")
# define COMMENT_ALPHA	"  %s{eoc} is " COLG("dominating") " !"
# define COMMENT_FIGHT	COLR("  The competitors are fighting to death")
# define INF_BAR1		"   " "Current period    >    %s{eoc}\n\n"
# define INF_BAR2		"   " "Last period       >    %s{eoc}\n\n"
# define INF_BARS		INF_BARMSG INF_BAR1 INF_BAR2

# define INF_SEPV		"  " SEPV "  "
# define INF_M2P1		"\n" "   " "To die " COLY("%4d") INF_SEPV
# define INF_M2P2		COLC("%2u") "/" COLG("%.2u") " Checks" INF_SEPV
# define INF_M2P3		"Last check " COLY("%6d") INF_SEPV
# define INF_M2P4		"Next check in " COLY("%4d")

# define INF_MSG2		INF_M2P1 INF_M2P2 INF_M2P3 INF_M2P4 "\n"

# define INF_MSG		INF_HEAD INF_MSG1 INF_BUFFSTAT INF_BARS INF_MSG2

/*
** -- VM ARENA STYLE --
*/

# define MEM_HEADER		COLG(">> MEMORY <<")"\n\n"

# define BPL			64

# define MEM_VALUE		COLB("   ") COLY("0x%4.4x") "   "

# define MEMSET_COLOR	COLC("%2.2hhx")
# define MEMZERO_COLOR	COLW("%2.2hhx")

# define COL_P0		"{white}"
# define BCOL_P0	"{b_black}"
# define COL_P1		"{blue}"
# define BCOL_P1	"{b_blue}"
# define COL_P2		"{yellow}"
# define BCOL_P2	"{b_yellow}"
# define COL_P3		"{red}"
# define BCOL_P3	"{b_red}"
# define COL_P4		"{green}"
# define BCOL_P4	"{b_green}"

# define PCC_P0		COLW("%2.2hhx")
# define PCC_P1		BCOL_P1 COLBK("%2.2hhx")
# define PCC_P2		BCOL_P2 COLBK("%2.2hhx")
# define PCC_P3		BCOL_P3 COLBK("%2.2hhx")
# define PCC_P4		BCOL_P4 COLBK("%2.2hhx")

/*
** -- VM REGISTERS STYLE --
*/

# define SEPV			COLB("|")
# define SEPC			COLB("+")
# define SEPL			COLB("--------") SEPC
# define SEPH			COLB("-")

# define REG_H1			"\t PID " COLY("%-4u") " <> Player " COLY("%u ")
# define REG_H2			SEPV " Carry " COLY("%u ") SEPV
# define REG_H3			" Pending > " COLG("%-6s") " - Timer " COLY("%4u")
# define REG_HEADER		COLG(">> REGISTERS <<") REG_H1 REG_H2 REG_H3 "\n"

# define REGSET_COLOR	COLY("%8.8x")
# define REGZERO_COLOR	COLW("%8.8x")

# define REG_BEGL1	 	"\n" "   " SEPC
# define REG_BEGL2		"\n" "   " SEPV
# define REGNO_FSZ		COLM("R") SEPH COLM("%2.2d")
# define REGN			COLB("--") REGNO_FSZ COLB("--") SEPC


#endif
