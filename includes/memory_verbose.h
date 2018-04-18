/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_verbose.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:03:51 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 01:41:03 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_VERBOSE_H
# define MEMORY_VERBOSE_H

/*
** -- COREWAR VM ARENA STYLE --
*/

# define MEM_HEADER		COLG(">> MEMORY <<")"\n\n"

# define BPL			32

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
** -- COREWAR VM REGISTERS STYLE --
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
