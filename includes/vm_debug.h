/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 02:10:18 by upopee            #+#    #+#             */
/*   Updated: 2018/05/02 20:54:02 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_DEBUG_H
# define VM_DEBUG_H

/*
** -- SEPARATORS --
*/

# define SEPV			COLB("|")
# define SEPVB			" " COLBBK(" ") " "
# define INF_SEPV		"  " SEPV "  "

/*
** -- GAME STATUS INFOS --
*/

# define INF_WIN		"inf"
# define IWA			INF_WIN, 0
# define INF_DEB		(c->d_level & CWDL_INF)

# define BAR_ECOLOR		"{b_black}"

# define INF_HEAD		COLG(">> INFO <<\n\n")

# define INF_PSQC		"%s" COLBK(" P%hhu ")
# define INF_NBLIVE		"Lives " COLG("%-5u")

# define INF_M1P1		"   " "Cycle " COLC("%-6d")
# define INF_M1P2		"%13s" "Processes " COLM("%-7u") "   " INF_NBLIVE
# define INF_M1P3		"   " "Last live  " INF_PSQC
# define INF_MSG1		INF_M1P1 INF_M1P2 INF_M1P3 "\n\n"

# define INF_PSTAT1		"    " INF_PSQC "  "
# define INF_PSTAT21	"  " "Childs " COLY("%-7u")
# define INF_PSTAT22	"   " INF_NBLIVE
# define INF_PSTAT23	"   " "Last live  " COLC("%u")
# define INF_PSTAT2		INF_PSTAT21 INF_PSTAT22 INF_PSTAT23 "\n\n"
# define INF_PNAME		"%s%-19s{eoc}"
# define INF_PNAMEL		"%s%-.16s...{eoc}"
# define INF_BUFFSTAT	"%s\n"

# define INF_BARMSG		"                          " "%s%50s\n\n"
# define COMMENT_NOONE	" {eoc}Nobody seems to be alive ... " COLM("PUSSIES !")
# define COMMENT_ALPHA	"  %s{eoc} is " COLG("dominating") " !"
# define COMMENT_FIGHT	COLR("  The competitors are fighting to death")
# define INF_BAR1		"   " "Current period    >    %s{eoc}\n\n"
# define INF_BAR2		"   " "Last period       >    %s{eoc}\n\n"
# define INF_BARS		INF_BARMSG INF_BAR1 INF_BAR2

# define INF_M2P1		"\n" "   " "To die " COLY("%4d") INF_SEPV
# define INF_M2P2		COLC("%2u") "/" COLG("%.2u") " Checks" INF_SEPV
# define INF_M2P3		"Last check " COLY("%6d") INF_SEPV
# define INF_M2P4		"Next check in " COLY("%4d")

# define INF_MSG2		INF_M2P1 INF_M2P2 INF_M2P3 INF_M2P4 "\n"

# define INF_MSG		INF_HEAD INF_MSG1 INF_BUFFSTAT INF_BARS INF_MSG2

/*
** -- ARENA DEBUG --
*/

# define MDA			cpu->memory, cpu->m_flags

# define MEM_WIN		"mem"
# define MEM_DEB		(cpu->ctrl->d_level & CWDL_MEM)

# define MEM_HEADER		COLG(">> MEMORY <<")"\n\n"

# define BPL			64

# define MEM_VALUE		COLB("   ") COLY("0x%4.4x") "   "

# define MEMWR_COLOR	"{bold}"
# define MEMSET_COLOR	"%2.2hhx{eoc}" " "
# define MEMZERO_COLOR	"{eoc}%2.2hhx" " "

# define COL_P0			"{white}"
# define BCOL_P0		"{b_black}"
# define COL_P1			"{blue}"
# define BCOL_P1		"{b_blue}"
# define COL_P2			"{yellow}"
# define BCOL_P2		"{b_yellow}"
# define COL_P3			"{red}"
# define BCOL_P3		"{b_red}"
# define COL_P4			"{green}"
# define BCOL_P4		"{b_green}"

# define PCC_P0			"{b_white}" COLBK("%2.2hhx") "{eoc} "
# define PCC_P1			BCOL_P1 COLW("%2.2hhx") COL_P1 " "
# define PCC_P2			BCOL_P2 COLW("%2.2hhx") COL_P2 " "
# define PCC_P3			BCOL_P3 COLW("%2.2hhx") COL_P3 " "
# define PCC_P4			BCOL_P4 COLW("%2.2hhx") COL_P4 " "

/*
** -- PROCESSES INFO --
*/

# define PROC			process
# define PROC_WIN		"proc"
# define PROC_DEB		(c->d_level & CWDL_PROC)
# define PWA			PROC_WIN, 0
# define PIA1			verb->color_buff[0], PROC->player_no, PROC->pid,
# define PIA2			PROC->birth, PROC->last_live,
# define PIA3			(PROC->next_op ? PROC->next_op->name : COLR("       ")),
# define PIA4			verb->color_buff[1], PROC->timer, PROC->pc,
# define PIA5			(PROC->carry ? COLG("1") : COLY("0"))
# define PIA			PIA1 PIA2 PIA3 PIA4 PIA5

# define PTIMER			"%s%-5hu{eoc}"
# define PCYCLE			COLC("%-7u")
# define POPNAME		COLG("%-7s")
# define PPC			COLM("%-4hu")
# define PPID			COLC(" ID ") COLY("%-7hu")
# define PCARRY			COLY("%s")

# define PHINF			COLY("%7u") " processes\t" COLY("%5u") " lives" "\n\n"
# define PH1			COLY(" PROCESS IDS ") SEPVB COLB(" BIRTH ") SEPVB
# define PH2			COLB("L. LIVE") SEPVB COLB("PENDING") SEPVB
# define PH3			COLB("TIMER") SEPVB COLB(" PC ") SEPVB COLB("C") SEPVB
# define PHL1			SEPVB PH1 PH2 PH3 "\n"
# define PHSEP			COLBBK(COLB("---------------------------------"))
# define PHL2			PHSEP PHSEP "\n"
# define PROC_HEADER	COLG(">> PROCESSES <<\t\t") PHINF PHL1 " " PHL2
# define PROC_I1		SEPVB D_PNO PPID SEPVB PCYCLE SEPVB PCYCLE
# define PROC_I2		SEPVB POPNAME SEPVB PTIMER SEPVB PPC SEPVB PCARRY SEPVB
# define PROC_INFOS		PROC_I1 PROC_I2 "\n"

# define TIMECOL_FAR	"{red}"
# define FAR_LIMIT		101
# define TIMECOL_NEAR	"{magenta}"
# define NEAR_LIMIT		31
# define TIMECOL_VNEAR	"{cyan}"
# define VNEAR_LIMIT	16
# define TIMECOL_IMM	"{yellow}"
# define IMM_LIMIT		6
# define TIMECOL_NOW	"{green}"

/*
** -- REGISTERS --
*/

# define REG_DEB		(cpu->ctrl->d_level & CWDL_REG)
# define REG_WIN		"reg"
# define RWA			REG_WIN, 0

# define PREGONE		COLC("%8.8x") SEPVB
# define PREGSET		COLY("%8.8x") SEPVB
# define PREGZERO		COLW("%8.8x") SEPVB

# define REGPIDS		"  {yellow}PROCESS IDS{blue}     "
# define REGNOS1		"R1         R2         R3         R4         "
# define REGNOS2		"R5         R6         R7         R8         "
# define REGNOS3		"R9         R10        R11        R12        "
# define REGNOS4		"R13        R14        R15        R16       "
# define REGNOS			REGPIDS REGNOS1 REGNOS2 REGNOS3 REGNOS4
# define REG_HEADER		COLG(">> REGISTERS <<") "\n\n " COLBBK(REGNOS) "\n"

# define REG_INFOS		SEPVB D_PNO PPID SEPVB
# define RWIA			verb->color_buff[0], process->player_no, process->pid

#endif
