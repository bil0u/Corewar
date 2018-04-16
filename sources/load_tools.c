/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:57:02 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 08:27:33 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "corewar.h"
#include "corewar_verbose.h"

/*
** - RETURNS NEXT PLAYER NUMBER AVAILABLE
*/

int		get_nextpno(uint16_t flags)
{
	if (!BIS_SET(flags, CWF_PNO(1)))
		return (1);
	else if (!BIS_SET(flags, CWF_PNO(2)))
		return (2);
	else if (!BIS_SET(flags, CWF_PNO(3)))
		return (3);
	else if (!BIS_SET(flags, CWF_PNO(4)))
		return (4);
	else
		return (0);
}

/*
** - CHECK IF ARG IS A VALID PLAYER NO
*/

int		is_valid_pno(int flags, int player_no)
{
	if (player_no == 0 || player_no > MAX_PLAYERS)
		return (log_this(NULL, LF_ERR, CWE_BADPNO, player_no));
	else if (BIS_SET(flags, CWF_PNO(player_no)))
		return (log_this(NULL, LF_ERR, CWE_PNOUSED, player_no));
	return (TRUE);
}

/*
** - CHECK IF ARG IS A VALID FILE
*/

int		is_valid_file(char *opt, t_cwvm *vm)
{
	int		fd;
	int		ret;
	uint8_t	p_no;

	if (!opt || opt[0] == '\0')
		return (log_this(NULL, LF_ERR, CWE_NOFILE));
	if ((fd = open(opt, O_RDONLY)) < 0)
		return (log_this(NULL, LF_ERR, CWE_UNKNOWN, opt));
	if ((p_no = vm->ctrl.next_pno) == 0)
		p_no = get_nextpno(vm->ctrl.flags);
	ret = load_binary(fd, vm->players + p_no - 1);
	close(fd);
	if (ret == FAILURE)
		return (log_this(NULL, LF_ERR, CWE_FILEKO, opt));
	vm->p_indexes[vm->nb_players] = p_no - 1;
	vm->players[p_no - 1].player_no = p_no;
	BSET(vm->ctrl.flags, CWF_PNO(p_no));
	vm->ctrl.next_pno = 0;
	++(vm->nb_players);
	return (TRUE);
}

/*
** - CHECK IF ARG IS A VALID OPTION
*/

int		is_valid_option(char *opt)
{
	if (opt[0] != '-' || opt[1] == '\0'
	|| !ft_strchr(VALID_OPT, opt[1]) || opt[2] != '\0')
			return (FALSE);
	return (TRUE);
}

/*
** - CHECK IF ARG IS A VALID NUMERIC VALUE
**   ac	->	main argc
**   av	->	main *argv[]
**   c	->	current arg position
*/

int			is_numeric(int argc, char **argv, int c)
{
	if (c < argc && argv[c][0] != '\0' && is_valid_option(argv[c]) == FALSE)
	{
		if (!ft_strisnumber(argv[c], '\0'))
			return (log_this(NULL, LF_ERR, CWE_NOTNUM, argv[c - 1], argv[c]));
		if (argv[c][0] == '-' || argv[c][0] == '+')
			return (log_this(NULL, LF_ERR, CWE_SIGN,
							argv[c - 1], argv[c], argv[c][0]));
		return (TRUE);
	}
	return (log_this(NULL, LF_ERR, CWE_NUMERIC, argv[c - 1]));
}
