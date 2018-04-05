/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:47:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 19:36:57 by upopee           ###   ########.fr       */
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
		opt == 'd' ? BSET(env->flags, CWF_DUMP) : (void)env;
		opt == 's' ? BSET(env->flags, CWF_SDMP) : (void)env;
		opt == 'v' ? BSET(env->flags, CWF_VERB) : (void)env;
		if (BSET(env->flags, CWF_SDMP | CWF_DUMP))
			env->nb_cycles = ft_atoi(argv[*cur]);
		opt == 'v' ? env->verbose_level = ft_atoi(argv[*cur]) : (void)env;
		opt == 'n' ? env->next_pno = ft_atoi(argv[*cur]) : (void)env;
		if (opt == 'n' && (is_valid_pno(env->flags, env->next_pno) != TRUE
		|| is_valid_file(argv[++(*cur)], env) != TRUE))
			return (FAILURE);
	}
	else
	{
		opt == 'V' ? BSET(env->flags, CWF_VISU) : (void)env;
		opt == 'S' ? BSET(env->flags, CWF_SLOW) : (void)env;
		opt == 'a' ? BSET(env->flags, CWF_AFFON) : (void)env;
	}
	return (SUCCESS);
}

static int	check_validity(t_cwdata *env)
{
	if (env->verbose_level >= CWVL_BAD)
		return (log_this(NULL, LF_ERR, CWE_BADVERB, env->verbose_level));
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

	if (argc == 1)
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
	t_player	*p_data;
	uint32_t	init_pos;
	t_process	new;

	curr_player = -1;
	ft_printf(CW_LOADING);
	while (++curr_player < env->nb_players)
	{
		init_pos = (MEM_SIZE / env->nb_players) * curr_player;
		p_data = env->players + curr_player;
		ft_memcpy(env->arena + init_pos, env->players_binaries + curr_player,
					p_data->header.prog_size);
		ft_bzero(&new, sizeof(new));
		new.registers[0] = REG_MAXVALUE - p_data->player_no;
		new.pc = init_pos;
		ft_lstadd(&p_data->processes, ft_lstnew(&new, sizeof(new)));
		++(p_data->nb_processes);
		ft_printf(CW_PLAYER, p_data->player_no, p_data->header.prog_size,
				p_data->header.prog_name, p_data->header.comment);
	}
}
