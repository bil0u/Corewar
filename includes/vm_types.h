/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 04:19:55 by upopee            #+#    #+#             */
/*   Updated: 2018/04/28 22:16:16 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_TYPES_H
# define VM_TYPES_H

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
# define PLAYER_RANGE			1024
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
	uint32_t		last_live;
	uint8_t			player_no;
	char			aff_buff[0xFF];
	uint8_t			aff_bytes;
}					t_player;

/*
** -- VERBOSE STRUCTURE
*/

# define BAR_BUFF_SIZE	(BAR_LEN << 1)
# define BAR_LEN		50
# define BAR_CROP		26
# define CROP_SPEED		2

typedef struct		s_vmverb
{
	char			color_buff[4][32];
	char			buff[LOG_BUFF_SIZE];
	char			comment[BAR_BUFF_SIZE];
	char			cbreakdown[BAR_BUFF_SIZE];
	char			lbreakdown[BAR_BUFF_SIZE];
	float			verb_carry;
	uint16_t		bytes_used;
	uint8_t			bar_crop;
}					t_vmverb;

/*
** -- VM PARAMETERS DATA
*/

# define RUN_SLOW		(c->flags & CWF_SLOW)

typedef struct		s_vmctrl
{
	uint32_t		dump_cycles;
	uint32_t		cycles_sec;
	useconds_t		sleep_time;
	uint16_t		flags;
	uint8_t			d_level;
	uint8_t			v_level;
	uint8_t			next_pno;
	t_vmverb		verbose;
}					t_vmctrl;

/*
** -- GAME RULES
*/

# define CYCLE_TO_DIE			1536
# define NBR_LIVE				21
# define CYCLE_DELTA			50
# define MAX_CHECKS				10
# define DUMP_WAIT				3

typedef struct		s_gamectrl
{
	uint8_t			*p_indexes;
	t_player		*players;
	uint32_t		nb_lives;
	uint32_t		last_check;
	int32_t			to_die;
	uint8_t			nb_players;
	uint8_t			nb_checks;
	uint8_t			winner;
	uint8_t			alpha;
}					t_gamectrl;

/*
** -- PROCESSES HANDLING
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

typedef struct s_vcpu			t_vcpu;

typedef struct		s_cwvm
{
	t_vmctrl		ctrl;
	t_jobctrl		jobs;
	t_gamectrl		game;
	t_vcpu			cpu;
	uint8_t			arena[MEM_SIZE];
	uint8_t			a_flags[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	uint8_t			p_indexes[MAX_PLAYERS];
	uint8_t			nb_players;
}					t_cwvm;

/*
** -- VERBOSE & DEBUG LEVELS
*/

# define CWVL_ESS				(0)
# define CWVL_LIVE				(1 << 0)
# define CWVL_CYCL				(1 << 1)
# define CWVL_INS				(1 << 2)
# define CWVL_KILL				(1 << 3)
# define CWVL_PC				(1 << 4)
# define CWVL_MAX				((CWVL_PC << 1) - 1)

# define CWDL_NONE				(0)
# define CWDL_INF				(1 << 0)
# define CWDL_MEM				(1 << 1)
# define CWDL_INS				(1 << 2)
# define CWDL_ARG				(1 << 3)
# define CWDL_PROC				(1 << 4)
# define CWDL_REG				(1 << 5)
# define CWDL_MAX				((CWDL_REG << 1) - 1)

/*
** -- GLOBAL FLAGS
*/

# define NB_OPTIONS				8
# define VALID_OPT				"avDdsVSz"
# define NUMERIC_OPT			"vDdsS"

# define CWF_AFFON				(1 << 0)
# define CWF_VERB				(1 << 1)
# define CWF_DEBUG				(1 << 2)
# define CWF_DUMP				(1 << 3)
# define CWF_SDMP				(1 << 4)
# define CWF_VISU				(1 << 5)
# define CWF_SLOW				(1 << 6)
# define CWF_ZBUG				(1 << 7)

# define CWF_PNO(x)				(1 << (NB_OPTIONS + (x - 1)))

/*
** -- COLOR FLAGS
*/

# define NB_CFLAGS				2

# define CWCF_NONE				(0)
# define CWCF_PC				(1 << 0)
# define CWCF_RWRITE			(1 << 1)

# define CWCF_PNO(x)			(1 << (NB_CFLAGS + (x - 1)))

#endif
