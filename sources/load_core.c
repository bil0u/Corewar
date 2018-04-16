/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:47:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 20:06:21 by upopee           ###   ########.fr       */
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

int			load_binary(int fd, t_player *p_dat)
{
	t_header	*info;
	uint32_t	nbr_buff;

	ft_bzero(p_dat, sizeof(*p_dat));
	info = &p_dat->header;
	if (read(fd, &nbr_buff, MAGIC_LENGTH) != MAGIC_LENGTH
	|| (info->magic = SWAP_UINT32(nbr_buff)) != COREWAR_EXEC_MAGIC
	|| read(fd, info->prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, &nbr_buff, PROG_SZ_LENGTH) != PROG_SZ_LENGTH
	|| (info->prog_size = SWAP_UINT32(nbr_buff)) == 0
	|| info->prog_size > CHAMP_MAX_SIZE
	|| read(fd, info->comment, COMMENT_LENGTH) != COMMENT_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, p_dat->binary, info->prog_size + 1) != info->prog_size)
		return (FAILURE);
	return (SUCCESS);
}

/*
** - CHECK IF AN ARG IS VALID AND SETS THE ASSOCIATED MODIFICATIONS IF TRUE
*/

static int	check_opt_args(int argc, char **argv, t_cwvm *vm, int *cur)
{
	char	*opt;

	opt = argv[*cur];
	if (ft_strchr(NUMERIC_OPT, opt[1]))
	{
		if (is_numeric(argc, argv, *cur + 1) != TRUE)
			return (FAILURE);
		++(*cur);
		opt[1] == 'd' ? BSET(vm->ctrl.flags, CWF_DUMP) : (void)0;
		opt[1] == 's' ? BSET(vm->ctrl.flags, CWF_SDMP) : (void)0;
		opt[1] == 'v' ? BSET(vm->ctrl.flags, CWF_VERB) : (void)0;
		opt[1] == 'v' ? vm->ctrl.verbose.level = ft_atoi(argv[*cur]) : (void)0;
		opt[1] == 'S' ? BSET(vm->ctrl.flags, CWF_SLOW) : (void)0;
		opt[1] == 'S' ? vm->ctrl.cycles_sec = ft_atoi(argv[*cur]) : (void)0;
		if (vm->ctrl.flags & (CWF_SDMP | CWF_DUMP))
			vm->ctrl.dump_cycles = ft_atoi(argv[*cur]);
		opt[1] == 'n' ? vm->ctrl.next_pno = ft_atoi(argv[*cur]) : (void)0;
		if (opt[1] == 'n' && (!is_valid_file(argv[++(*cur)], vm)
		|| is_valid_pno(vm->ctrl.flags, vm->ctrl.next_pno)))
			return (FAILURE);
		return (SUCCESS);
	}
	opt[1] == 'V' ? BSET(vm->ctrl.flags, CWF_VISU) : (void)0;
	opt[1] == 'a' ? BSET(vm->ctrl.flags, CWF_AFFON) : (void)0;
	return (SUCCESS);
}

/*
** - FINAL CHECK OF LOADED VALUES BEFORE EXECUTION
*/

static int	check_validity(t_cwvm *vm)
{
	if (vm->ctrl.verbose.level > CWVL_MAX)
		return (log_this(NULL, LF_ERR, CWE_BADVERB, vm->ctrl.verbose.level));
	if (vm->nb_players == 0)
		return (log_this(NULL, LF_ERR, CWE_NOPLAYERS));
	return (SUCCESS);
}

/*
** - CHECK ALL ARGV ARGUMENTS
*/

int		 	check_argv(int argc, char **argv, t_cwvm *vm)
{
	int		valid;
	int		curr_arg;

	if (argc == 1 || ft_strequ(argv[1], "-h"))
		return (err_msg(CW_USAGE));
	curr_arg = 0;
	while (++curr_arg < argc)
		if ((valid = is_valid_option(argv[curr_arg])) == TRUE)
		{
			if (check_opt_args(argc, argv, vm, &curr_arg) != SUCCESS)
				return (FAILURE);
		}
		else if ((valid = is_valid_file(argv[curr_arg], vm)) != TRUE)
			return (FAILURE);
		if (valid != TRUE)
			return (log_this(NULL, LF_ERR, CWE_BADOPT, argv[curr_arg]));
	return (check_validity(vm));
}

/*
** - LOAD GAME IN ARENA AND INITIALIZE THE REMAINING VALUES OF ENV
*/

void		load_players(t_cwvm *vm)
{
	t_player	*dat;
	int			curr_p;
	uint32_t	init;
	t_process	new;

	log_this("chp", LF_BOTH, CW_LOADING);
	curr_p = -1;
	while (++curr_p < vm->nb_players)
	{
		dat = vm->players + vm->p_indexes[curr_p];
		init = (MEM_SIZE / vm->nb_players) * vm->p_indexes[curr_p];
		++(dat->nb_processes);
		++(vm->jobs.next_pid);
		ft_bzero(&new, sizeof(new));
		new.pid = vm->jobs.next_pid;
		new.player_no = dat->player_no;
		new.last_live = 1;
		new.registers[0] = REG_MAXVALUE - (new.player_no - 1);
		new.pc = init;
		ft_lstadd(&vm->jobs.p_stack, ft_lstnew(&new, sizeof(new)));
		ft_memcpy(vm->arena + init, dat->binary, dat->header.prog_size);
		log_this("chp", LF_BOTH, CW_PLAYER, dat->player_no,
			dat->header.prog_size, dat->header.prog_name, dat->header.comment);
	}
}
