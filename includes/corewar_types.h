/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 04:19:55 by upopee            #+#    #+#             */
/*   Updated: 2018/03/30 20:13:57 by upopee           ###   ########.fr       */
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

#endif
