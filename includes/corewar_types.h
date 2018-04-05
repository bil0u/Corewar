/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 04:19:55 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 14:59:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_TYPES_H
# define COREWAR_TYPES_H

# define MEM_SIZE				64				// TEST VALUE - TO BE MODIFIED
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

typedef struct		s_process
{
	uint32_t		registers[REG_NUMBER];
	uint32_t		pid;
	uint32_t		pc;
	uint32_t		timer;
	uint32_t		last_live;
	uint8_t			carry;
}					t_process;

typedef struct		s_player
{
	uint32_t		player_no;
	t_header		header;
	t_list			*processes;
}					t_player;

typedef struct		s_cwdata
{
	t_vcpu			cpu;
	uint8_t			arena[MEM_SIZE];
	uint32_t		nb_cycles;
	t_player		players[MAX_PLAYERS];
	int				players_files[MAX_PLAYERS];
	uint8_t			players_binaries[MAX_PLAYERS][CHAMP_MAX_SIZE];
	uint16_t		flags;
	uint8_t			nb_players;
	uint8_t			next_pno;
	uint8_t			verbose_level;
}					t_cwdata;

# define CWF_PNO(x)	(1 << (x - 1))

# define CWF_VERB	(1 << 4)
# define CWF_DUMP	(1 << 5)
# define CWF_SDMP	(1 << 6)
# define CWF_NCUR	(1 << 7)
# define CWF_VISU	(1 << 8)
# define CWF_AFFON	(1 << 9)
# define CWF_SLOW	(1 << 10)

#endif
