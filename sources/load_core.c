/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:47:46 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 07:53:50 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vcpu_types.h"
#include "corewar_types.h"
#include "corewar.h"
#include "load_verbose.h"
#include "corewar_verbose.h"


/*
** - LOAD A BINARY FILE
*/

static int	load_binary(int fd, t_player *p_dat)
{
	t_header	*info;
	uint32_t	nbr_buff;

	ft_bzero(p_dat, sizeof(*p_dat));
	info = &p_dat->header;
	if (read(fd, &nbr_buff, MAGIC_LENGTH) != MAGIC_LENGTH
	|| (info->magic = SWAP_UINT32(nbr_buff)) != COREWAR_EXEC_MAGIC
	|| read(fd, info->pname, PROG_NAME_LENGTH) != PROG_NAME_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, &nbr_buff, PROG_SZ_LENGTH) != PROG_SZ_LENGTH
	|| (info->psize = SWAP_UINT32(nbr_buff)) == 0
	|| info->psize > CHAMP_MAX_SIZE
	|| read(fd, info->comment, COMMENT_LENGTH) != COMMENT_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, p_dat->binary, info->psize + 1) != info->psize)
		return (FAILURE);
	return (SUCCESS);
}

/*
** - CHECK IF AN ARG IS VALID AND SETS THE ASSOCIATED MODIFICATIONS IF TRUE
*/

static int	parse_option(t_vmctrl *c, int ac, char **av, int *i)
{
	uint16_t	invalid;
	char		*opt;

	opt = av[*i];
	invalid = 0;
	if (ft_strchr(NUMERIC_OPT, opt[1]) && is_numeric(ac, av, ++(*i)) != TRUE)
		return (FAILURE);
	opt[1] == 'a' ? BSET(c->flags, CWF_AFFON) : ++invalid;
	opt[1] == 'v' ? BSET(c->flags, CWF_VERB) : ++invalid;
	opt[1] == 'd' ? BSET(c->flags, CWF_DUMP) : ++invalid;
	opt[1] == 'V' ? BSET(c->flags, CWF_VISU) : ++invalid;
	opt[1] == 's' ? BSET(c->flags, CWF_DUMP | CWF_SDMP) : ++invalid;
	opt[1] == 'S' ? c->cycles_sec = ft_atoi(av[*i]) : ++invalid;
	opt[1] == 'v' ? c->verbose.level = ft_atoi(av[*i]) : (void)0;
	c->flags & CWF_DUMP ? c->dump_cycles = ft_atoi(av[*i]) : (void)0;
	if (invalid == NB_OPTIONS)
		return (log_this(NULL, LF_ERR, CWE_BADOPT, opt));
	return (SUCCESS);
}

/*
** - PARSE PLAYER FILE - RETURNS TRUE UPON SUCCESS
*/

static int	parse_player(t_cwvm *v, int ac, char **av, int *i)
{
	int		fd;
	int		ret;
	uint8_t	p;

	if (av[*i][0] == '-')
	{
		if (av[*i][1] != 'n' || av[*i][2] != '\0')
			return (log_this(NULL, LF_ERR, CWE_BADOPT, av[*i]));
		else if (is_valid_pno(&v->ctrl, ac, av, i) != TRUE)
			return (FAILURE);
	}
	if ((fd = open(av[*i], O_RDONLY)) < 0)
		return (log_this(NULL, LF_ERR, CWE_UNKNOWN, av[*i]));
	p = (v->ctrl.next_pno != 0 ? v->ctrl.next_pno : get_nextpno(v->ctrl.flags));
	ret = load_binary(fd, v->players + p - 1);
	close(fd);
	if (ret == FAILURE)
		return (log_this(NULL, LF_ERR, CWE_FILEKO, av[*i]));
	v->p_indexes[v->nb_players++] = p - 1;
	v->players[p - 1].player_no = p;
	BSET(v->ctrl.flags, CWF_PNO(p));
	v->ctrl.next_pno = 0;
	return (SUCCESS);
}

/*
** - CHECK ALL ARGV ARGUMENTS
*/

int		 	check_argv(int ac, char **av, t_cwvm *vm)
{
	int		curr_arg;

	if (ac == 1 || ft_strequ(av[1], "-h"))
		return (err_msg(CW_USAGE));
	curr_arg = 0;
	while (++curr_arg < ac)
	{
		if (av[curr_arg][0] == '\0')
			continue ;
		if (is_option(av[curr_arg]) == TRUE)
		{
			if (parse_option(&vm->ctrl, ac, av, &curr_arg) != SUCCESS)
				return (FAILURE);
		}
		else if (parse_player(vm, ac, av, &curr_arg) != SUCCESS)
			return (FAILURE);
	}
	if (vm->ctrl.verbose.level > CWVL_MAX)
		return (log_this(NULL, LF_ERR, CWE_BADVERB, vm->ctrl.verbose.level));
	if (vm->nb_players == 0)
		return (log_this(NULL, LF_ERR, CWE_NOPLAYERS));
	return (SUCCESS);
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
		init = (MEM_SIZE / vm->nb_players) * curr_p;
		++(dat->nb_processes);
		++(vm->jobs.next_pid);
		ft_bzero(&new, sizeof(new));
		new.pid = vm->jobs.next_pid;
		new.player_no = dat->player_no;
		new.last_live = 1;
		new.registers[0] = REG_MAXVALUE - (new.player_no - 1);
		new.pc = init;
		ft_lstadd(&vm->jobs.p_stack, ft_lstnew(&new, sizeof(new)));
		ft_memcpy(vm->arena + init, dat->binary, dat->header.psize);
		log_this("chp", LF_BOTH, CW_PLAYER, dat->player_no,
			dat->header.psize, dat->header.pname, dat->header.comment);
	}
}
