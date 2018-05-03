/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:47:46 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 22:52:29 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "sdl_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "vm_verbose.h"

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
	opt[1] == 'D' ? BSET(c->flags, CWF_DEBUG) : ++invalid;
	opt[1] == 'd' ? BSET(c->flags, CWF_DUMP) : ++invalid;
	opt[1] == 's' ? BSET(c->flags, CWF_DUMP | CWF_SDMP) : ++invalid;
	opt[1] == 'V' ? BSET(c->flags, CWF_VISU) : ++invalid;
	opt[1] == 'S' ? BSET(c->flags, CWF_SLOW) : ++invalid;
	opt[1] == 'z' ? BSET(c->flags, CWF_ZBUG) : ++invalid;
	opt[1] == 'v' ? c->v_level = ft_atoi(av[*i]) : 0;
	opt[1] == 'D' ? c->d_level = ft_atoi(av[*i]) : 0;
	opt[1] == 'S' ? c->cycles_sec = ft_atoi(av[*i]) : 0;
	opt[1] == 'd' || opt[1] == 's' ? c->dump_cycles = ft_atoi(av[*i]) : 0;
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
	if (v->nb_players == MAX_PLAYERS)
		return (log_this(NULL, LF_ERR, CWE_MAXPLAYER));
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

int			check_argv(int ac, char **av, t_cwvm *vm)
{
	int		curr_arg;

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
	if (vm->ctrl.v_level > CWVL_MAX)
		return (log_this(NULL, LF_ERR, CWE_BADVL, vm->ctrl.v_level, CWVL_MAX));
	if (vm->ctrl.d_level > CWDL_MAX)
		return (log_this(NULL, LF_ERR, CWE_BADDL, vm->ctrl.d_level, CWDL_MAX));
	if (vm->nb_players == 0)
		return (log_this(NULL, LF_ERR, CWE_NOPLAYERS));
	return (SUCCESS);
}

/*
** - LOAD THE PLAYERS BINARIES IN ARENA AND INITIALIZE ASSOCIATED PARAMETERS
*/

int			load_players(t_cwvm *vm)
{
	t_player	*p_data;
	t_header	*head;
	uint16_t	pos;
	int			curr_player;

	ft_printf(vm->ctrl.flags & CWF_VERB ? CW_ZLOADING : CW_LOADING);
	curr_player = -1;
	while (++curr_player < vm->nb_players)
	{
		p_data = vm->players + vm->p_indexes[curr_player];
		head = &p_data->header;
		pos = (MEM_SIZE / vm->nb_players) * curr_player;
		ft_memcpy(vm->arena + pos, p_data->binary, head->psize);
		ft_u16set(vm->a_flags + pos, CWCF_PNO(p_data->player_no), head->psize);
		if (!dup_process(&vm->cpu, p_data, NULL, pos))
			return (FAILURE);
		ft_printf((vm->ctrl.flags & CWF_VERB ? CW_ZPLAYER : CW_PLAYER),
			p_data->player_no, head->psize, head->pname, head->comment);
	}
	return (SUCCESS);
}
