/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 04:19:55 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 19:24:09 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_TYPES_H
# define COREWAR_TYPES_H

# define MEM_SIZE				512				// TEST VALUE - TO BE MODIFIED
# define IDX_MOD				(MEM_SIZE)		// TEST VALUE - TO BE MODIFIED
# define CHAMP_MAX_SIZE			(MEM_SIZE)		// TEST VALUE - TO BE MODIFIED
# define MAX_PLAYERS			4

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

# define REG_NUMBER				8
# define REG_SIZE				4
# define REG_LEN				(REG_NUMBER * REG_SIZE)
# define REG_MAXVALUE			((1UL << (REG_SIZE * CHAR_BIT)) - 1)

typedef struct		s_process
{
	uint32_t		registers[REG_NUMBER];
	uint32_t		pc;
	uint32_t		timer;
	uint32_t		last_live;
	uint8_t			carry;
}					t_process;

typedef struct		s_player
{
	t_header		header;
	uint32_t		player_no;
	uint32_t		nb_processes;
	t_list			*processes;
	t_list			*pending;
}					t_player;

typedef struct		s_cwdata
{
	t_vcpu			cpu;
	uint8_t			arena[MEM_SIZE];
	uint32_t		nb_cycles;
	t_player		players[MAX_PLAYERS];
	uint8_t			players_binaries[MAX_PLAYERS][CHAMP_MAX_SIZE];
	uint16_t		flags;
	uint16_t		verbose_level;
	uint8_t			nb_players;
	uint8_t			next_pno;
}					t_cwdata;

# define CWF_PNO(x)				(1 << (x - 1))

# define CWVL_ESS				(0 << 0)
# define CWVL_LIVE				(1 << 0)
# define CWVL_CYCL				(1 << 1)
# define CWVL_ARG				(1 << 2)
# define CWVL_DIE				(1 << 3)
# define CWVL_PC				(1 << 4)
# define CWVL_DEBUG				(1 << 5)
# define CWVL_BAD				(1 << 6)

# define CWF_VERB				(1 << 4)
# define CWF_DUMP				(1 << 5)
# define CWF_SDMP				(1 << 6)
# define CWF_NCUR				(1 << 7)
# define CWF_VISU				(1 << 8)
# define CWF_AFFON				(1 << 9)
# define CWF_SLOW				(1 << 10)

#endif
