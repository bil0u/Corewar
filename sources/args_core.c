/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:47:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/05 15:34:33 by upopee           ###   ########.fr       */
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
		opt == 'd' ? env->nb_cycles = ft_atoi(argv[*cur]) : (void)env;
		opt == 's' ? BSET(env->flags, CWF_SDMP) : (void)env;
		opt == 's' ? env->nb_cycles = ft_atoi(argv[*cur]) : (void)env;
		opt == 'v' ? BSET(env->flags, CWF_VERB) : (void)env;
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
	return (SUCCESS);
}
