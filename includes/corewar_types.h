/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 04:19:55 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 16:37:13 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_TYPES_H
# define COREWAR_TYPES_H

/*
** -- VIRTUAL MACHINE FIXED VARIABLES -- /!\ WARNING /!\ --
**    > MEM_SIZE must be a power of 2 (1 << X)
**    > CHAMP_MAX_SIZE must be set at MEM_SIZE / MAX_PLAYERS maximum
**      - ideally : (MEM_SIZE / 6)
**    > IDX_MOD should be set at MEM_SIZE / MAX_PLAYERS maximum
**      - ideally : (MEM_SIZE / 8)
**    > CPS_DEFAULT is the cycles per second limit in visu or debug mode
1**      - ideally : 50
*/

# define MAX_PLAYERS			4
# define PLAYER_RANGE			512
# define MEM_SIZE				(MAX_PLAYERS * PLAYER_RANGE)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define IDX_MOD				(MEM_SIZE / 8)
# define CPS_DEFAULT			50

/*
** -- BINARY FILE SIZES --
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
	char			pname[PROG_NAME_LENGTH + 1];
	uint32_t		psize;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

/*
** -- PLAYER DATA --
*/

typedef struct		s_player
{
	t_header		header;
	uint8_t			binary[CHAMP_MAX_SIZE];
	uint32_t		nb_processes;
	uint32_t		nb_lives;
	int32_t			last_live;
	uint8_t			player_no;
	char			aff_buff[0xFF];
	uint8_t			aff_bytes;
}					t_player;

/*
** -- VM PARAMETERS DATA
*/

# define BAR_BUFF_SIZE	(BAR_LEN << 1)
# define BAR_LEN		50
# define BAR_CROP		26
# define CROP_SPEED		2

typedef struct		s_vmverb
{
	char			color_buff[4][32];
	char			stats[BAR_BUFF_SIZE * (MAX_PLAYERS << 1)];
	char			comment[BAR_BUFF_SIZE];
	char			cbreakdown[BAR_BUFF_SIZE];
	char			lbreakdown[BAR_BUFF_SIZE];
	float			verb_carry;
	uint16_t		bytes_used;
	uint16_t		level;
	uint8_t			log_flags;
	uint8_t			bar_crop;
}					t_vmverb;

/*
** -- VM PARAMETERS DATA
*/

typedef struct		s_vmctrl
{
	uint32_t		dump_cycles;
	useconds_t		sleep_time;
	uint16_t		cycles_sec;
	uint16_t		flags;
	uint8_t			next_pno;
	t_vmverb		verbose;
}					t_vmctrl;

/*
** -- GAME PARAMETERS
*/

# define CYCLE_TO_DIE			1536
# define NBR_LIVE				21
# define CYCLE_DELTA			50
# define MAX_CHECKS				10
# define DUMP_WAIT				3

typedef struct		s_gamectrl
{
	uint32_t		nb_lives;
	int32_t			to_die;
	int32_t			last_check;
	uint8_t			nb_checks;
	uint8_t			winner;
	uint8_t			alpha;
}					t_gamectrl;

/*
** -- PROCESSES HANDLING DATA STRUCTURE
*/

typedef struct		s_jobctrl
{
	t_list			*p_stack;
	uint32_t		nb_processes;
	uint32_t		next_pid;
}					t_jobctrl;

/*
** -- COREWAR VIRTUAL MACHINE ENVIRONMENT
*/

typedef struct		s_vcpu t_vcpu;

typedef struct		s_cwvm
{
	t_vmctrl		ctrl;
	t_jobctrl		jobs;
	t_gamectrl		game;
	t_vcpu			cpu;
	uint8_t			arena[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	uint8_t			p_indexes[MAX_PLAYERS];
	uint8_t			nb_players;
}					t_cwvm;

/*
** -- VERBOSE FLAGS
*/

# define CWVL_ESS				(0 << 0)
# define CWVL_LIVE				(1 << 0)
# define CWVL_CYCL				(1 << 1)
# define CWVL_ARG				(1 << 2)
# define CWVL_DIE				(1 << 3)
# define CWVL_PC				(1 << 4)
# define CWVL_DEBUG				(1 << 5)
# define CWVL_MAX				((CWVL_DEBUG << 1) - 1)

/*
** -- GLOBAL FLAGS
*/

# define NB_OPTIONS				6
# define VALID_OPT				"aSvdsV"
# define NUMERIC_OPT			"Svds"

# define CWF_AFFON				(1 << 0)
# define CWF_VERB				(1 << 1)
# define CWF_DUMP				(1 << 2)
# define CWF_SDMP				(1 << 3)
# define CWF_VISU				(1 << 4)

# define CWF_PNO(x)				(1 << (NB_OPTIONS + (x - 1)))

#endif
