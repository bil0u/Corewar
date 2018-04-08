/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:47:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/08 09:24:44 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "corewar.h"
#include "corewar_verbose.h"

/*
** - LOAD A BINARY FILE
*/

int			load_binary(int fd, t_player *pbuff, uint8_t *mbuff)
{
	uint32_t	nbr_buff;

	ft_bzero(pbuff, sizeof(*pbuff));
	if (read(fd, &nbr_buff, MAGIC_LENGTH) != MAGIC_LENGTH
	|| (pbuff->header.magic = SWAP_UINT32(nbr_buff)) != COREWAR_EXEC_MAGIC
	|| read(fd, pbuff->header.prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, &nbr_buff, PROG_SZ_LENGTH) != PROG_SZ_LENGTH
	|| (pbuff->header.prog_size = SWAP_UINT32(nbr_buff)) == 0
	|| pbuff->header.prog_size > CHAMP_MAX_SIZE
	|| read(fd, pbuff->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, mbuff, pbuff->header.prog_size + 1) != pbuff->header.prog_size)
		return (FAILURE);
	return (SUCCESS);
}

/*
** - CHECK IF AN ARG IS VALID AND SETS THE ASSOCIATED MODIFICATIONS
*/

static int	check_opt_args(int argc, char **argv, t_cwdata *env, int *cur)
{
	char	opt;

	opt = argv[*cur][1];
	if (ft_strchr(NUMERIC_OPT, opt))
	{
		if (is_numeric(argc, argv, *cur + 1) != TRUE)
			return (FAILURE);
		++(*cur);
		opt == 'd' ? BSET(env->control.flags, CWF_DUMP) : (void)0;
		opt == 's' ? BSET(env->control.flags, CWF_SDMP) : (void)0;
		opt == 'v' ? BSET(env->control.flags, CWF_VERB) : (void)0;
		opt == 'v' ? env->control.verb_level = ft_atoi(argv[*cur]) : (void)0;
		if (BIS_SET(env->control.flags, CWF_SDMP | CWF_DUMP))
			env->control.nb_cycles = ft_atoi(argv[*cur]);
		opt == 'n' ? env->control.next_pno = ft_atoi(argv[*cur]) : (void)0;
		if (opt == 'n' &&
		(is_valid_pno(env->control.flags, env->control.next_pno) != TRUE
		|| is_valid_file(argv[++(*cur)], env) != TRUE))
			return (FAILURE);
	}
	else
	{
		opt == 'V' ? BSET(env->control.flags, CWF_VISU) : (void)0;
		opt == 'S' ? BSET(env->control.flags, CWF_SLOW) : (void)0;
		opt == 'a' ? BSET(env->control.flags, CWF_AFFON) : (void)0;
	}
	return (SUCCESS);
}

static int	check_validity(t_cwdata *env)
{
	if (env->control.verb_level >= CWVL_BAD)
		return (log_this(NULL, LF_ERR, CWE_BADVERB, env->control.verb_level));
	if (env->nb_players == 0)
		return (log_this(NULL, LF_ERR, CWE_NOPLAYERS));
	return (SUCCESS);
}

/*
** - CHECK ALL ARGV ARGUMENTS
*/

int		 	check_argv(int argc, char **argv, t_cwdata *env)
{
	int		valid;
	int		curr_arg;

	if (argc == 1 || ft_strequ(argv[1], "-h"))
		return (err_msg(CW_USAGE));
	curr_arg = 0;
	while (++curr_arg < argc)
		if ((valid = is_valid_option(argv[curr_arg])) == TRUE)
		{
			if (check_opt_args(argc, argv, env, &curr_arg) != SUCCESS)
				return (FAILURE);
		}
		else if ((valid = is_valid_file(argv[curr_arg], env)) != TRUE)
			return (FAILURE);
		if (valid != TRUE)
			return (log_this(NULL, LF_ERR, CWE_BADOPT, argv[curr_arg]));
	return (check_validity(env));
}

/*
** - LOAD GAME IN ARENA AND INITIALIZE THE REMAINING VALUES OF ENV
*/

void		load_players(t_cwdata *env)
{
	int			curr_player;
	t_player	*p;
	uint32_t	init_pos;
	t_process	new;

	curr_player = -1;
	ft_printf(CW_LOADING);
	log_this("chp", 0, CW_LOADING);
	while (++curr_player < env->nb_players)
	{
		init_pos = (MEM_SIZE / env->nb_players) * curr_player;
		p = env->players + curr_player;
		ft_memcpy(env->arena + init_pos, env->players_binaries + curr_player,
					p->header.prog_size);
		ft_bzero(&new, sizeof(new));
		new.registers[0] = REG_MAXVALUE - (p->player_no - 1);
		new.pc = init_pos;
		ft_lstadd(&p->processes, ft_lstnew(&new, sizeof(new)));
		++(p->nb_processes);
		p->pending = p->processes;
		ft_printf(CW_PLAYER, p->player_no, p->header.prog_size,
				p->header.prog_name, p->header.comment);
		log_this("chp", 0, CW_PLAYER, p->player_no, p->header.prog_size,
				p->header.prog_name, p->header.comment);
	}
}
