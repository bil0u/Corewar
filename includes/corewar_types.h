/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 04:19:55 by upopee            #+#    #+#             */
/*   Updated: 2018/04/12 06:48:18 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_TYPES_H
# define COREWAR_TYPES_H

/*
** -- ENVIRONMENT SIZES -- /!\ WARNING /!\ --
**    > MEM_SIZE must be a power of 2 (1 << X)
**    > CHAMP_MAX_SIZE must be set at MEM_SIZE / MAX_PLAYERS maximum
**      - ideally : (MEM_SIZE / 6)
**    > IDX_MOD should be set at MEM_SIZE / MAX_PLAYERS maximum
**      - ideally : (MEM_SIZE / 8)
*/

# define MAX_PLAYERS			4
# define MEM_SIZE				(1 << 9)		// TEST VALUE - TO BE MODIFIED
# define CHAMP_MAX_SIZE			(MEM_SIZE)		// TEST VALUE - TO BE MODIFIED
# define IDX_MOD				(MEM_SIZE)		// TEST VALUE - TO BE MODIFIED

/*
** -- GAME PARAMETERS --
*/

# define CYCLE_TO_DIE			1536
# define NBR_LIVE				21
# define CYCLE_DELTA			50
# define MAX_CHECKS				10

# define PRINT_BUFF_SIZE		(MEM_SIZE << 4)

/*
** -- BINARY LOADING PARAMETERS --
*/

# define SPACING_LENGTH			4
# define MAGIC_LENGTH			4
# define PROG_SZ_LENGTH			4
# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_header
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

/*
** -- PROCESS ELEMENTS --
*/

# define REG_NUMBER				16
# define REG_SIZE				4
# define REG_LEN				(REG_NUMBER * REG_SIZE)
# define REG_MAXVALUE			((1UL << (REG_SIZE * CHAR_BIT)) - 1)

typedef struct		s_process
{
	uint32_t		pid;
	uint32_t		registers[REG_NUMBER];
	uint32_t		pc;
	uint32_t		timer;
	uint32_t		last_live;
	uint8_t			carry;
	uint8_t			player_no;
	t_op			*next_op;
}					t_process;

/*
** -- PLAYER DATA --
*/

typedef struct		s_player
{
	t_header		header;
	uint32_t		nb_processes;
	uint8_t			player_no;
}					t_player;

/*
** -- GLOBAL ENV & DATA STRUCTURE - WITH VERBOSE & GLOBAL FLAGS
*/

# define CWVL_ESS				(0 << 0)
# define CWVL_LIVE				(1 << 0)
# define CWVL_CYCL				(1 << 1)
# define CWVL_ARG				(1 << 2)
# define CWVL_DIE				(1 << 3)
# define CWVL_PC				(1 << 4)
# define CWVL_DEBUG				(1 << 5)
# define CWVL_BAD				(1 << 6)

typedef struct		s_pcontrol
{
	uint32_t		nb_processes;
	uint32_t		tot_processes;
	uint32_t		nb_cycles;
	uint32_t		last_check;
	uint32_t		nb_checks;
	uint32_t		to_die;
	uint32_t		nb_lives;
	uint16_t		verb_level;
	uint16_t		flags;
	uint8_t			l_flags;
	uint8_t			winner;
	uint8_t			next_pno;
	useconds_t		sleep_us;
}					t_pcontrol;

# define CWF_PNO(x)				(1 << (x - 1))

# define CWF_VERB				(1 << 4)
# define CWF_DUMP				(1 << 5)
# define CWF_SDMP				(1 << 6)
# define CWF_NCUR				(1 << 7)
# define CWF_VISU				(1 << 8)
# define CWF_AFFON				(1 << 9)
# define CWF_SLOW				(1 << 10)

typedef struct		s_cwdata
{
	t_vcpu			cpu;
	t_pcontrol		control;
	uint8_t			arena[MEM_SIZE];
	t_list			*processes;
	t_player		players[MAX_PLAYERS];
	uint8_t			p_indexes[MAX_PLAYERS];
	uint8_t			p_binaries[MAX_PLAYERS][CHAMP_MAX_SIZE];
	uint8_t			nb_players;
}					t_cwdata;

#endif
