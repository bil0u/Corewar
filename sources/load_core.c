/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:47:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/12 05:09:48 by upopee           ###   ########.fr       */
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
** - CHECK IF AN ARG IS VALID AND SETS THE ASSOCIATED MODIFICATIONS IF TRUE
*/

static int	check_opt_args(int argc, char **argv, t_cwdata *e, int *cur)
{
	char	*opt;

	opt = argv[*cur];
	if (ft_strchr(NUMERIC_OPT, opt[1]))
	{
		if (is_numeric(argc, argv, *cur + 1) != TRUE)
			return (FAILURE);
		++(*cur);
		opt[1] == 'd' ? BSET(e->control.flags, CWF_DUMP) : (void)0;
		opt[1] == 's' ? BSET(e->control.flags, CWF_SDMP) : (void)0;
		opt[1] == 'v' ? BSET(e->control.flags, CWF_VERB) : (void)0;
		opt[1] == 'v' ? e->control.verb_level = ft_atoi(argv[*cur]) : (void)0;
		opt[1] == 'S' ? BSET(e->control.flags, CWF_SLOW) : (void)0;
		opt[1] == 'S' ? e->control.sleep_us = ft_atoi(argv[*cur]) : (void)0;
		if (e->control.flags & (CWF_SDMP | CWF_DUMP))
			e->control.nb_cycles = ft_atoi(argv[*cur]);
		opt[1] == 'n' ? e->control.next_pno = ft_atoi(argv[*cur]) : (void)0;
		if (opt[1] == 'n' && (!is_valid_file(argv[++(*cur)], e)
		|| is_valid_pno(e->control.flags, e->control.next_pno)))
			return (FAILURE);
		return (SUCCESS);
	}
	opt[1] == 'V' ? BSET(e->control.flags, CWF_VISU) : (void)0;
	opt[1] == 'a' ? BSET(e->control.flags, CWF_AFFON) : (void)0;
	return (SUCCESS);
}

/*
** - FINAL CHECK OF LOADED VALUES BEFORE EXECUTION
*/

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

void		load_players(t_cwdata *e, t_player *players)
{
	t_player	*p_data;
	int			curr_p;
	uint32_t	init_pos;
	t_process	new;

	log_this("chp", e->control.verb_level & (LF_BOTH), CW_LOADING);
	curr_p = -1;
	while (++curr_p < e->nb_players)
	{
		p_data = players + e->p_indexes[curr_p];
		init_pos = (MEM_SIZE / e->nb_players) * e->p_indexes[curr_p];
		++(p_data->nb_processes);
		++(e->control.tot_processes);
		ft_bzero(&new, sizeof(new));
		new.pid = e->control.tot_processes;
		new.player_no = p_data->player_no;
		new.registers[0] = REG_MAXVALUE - (p_data->player_no - 1);
		new.pc = init_pos;
		ft_lstadd(&e->processes, ft_lstnew(&new, sizeof(new)));
		ft_memcpy(e->arena + init_pos, e->p_binaries + e->p_indexes[curr_p], p_data->header.prog_size);
		log_this("chp", LF_BOTH, CW_PLAYER, p_data->player_no, p_data->header.prog_size,
				p_data->header.prog_name, p_data->header.comment);
	}
}
