/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:57:02 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 03:09:52 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "vm.h"
#include "vm_verbose.h"

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

int		is_valid_pno(t_vmctrl *ctrl, int ac, char **av, int *i)
{
	if (is_numeric(ac, av, ++(*i)) != TRUE)
		return (FALSE);
	ctrl->next_pno = ft_atoi(av[(*i)++]);
	if (ctrl->next_pno == 0 || ctrl->next_pno > MAX_PLAYERS)
		return (log_this(NULL, LF_ERR, CWE_BADPNO, ctrl->next_pno));
	else if (ctrl->flags & CWF_PNO(ctrl->next_pno))
		return (log_this(NULL, LF_ERR, CWE_PNOUSED, ctrl->next_pno));
	if (*i == ac || av[*i][0] == '\0')
		return (log_this(NULL, LF_ERR, CWE_NOFILE, av[*i - 2], av[*i - 1]));
	else if (is_option(av[*i]))
		return (log_this(NULL, LF_ERR, CWE_NOTFILE, av[*i]));
	return (TRUE);
}


/*
** - CHECK IF ARG IS A VALID OPTION
*/

int		is_option(char *opt)
{
	if (opt[0] != '-' || opt[1] == '\0' || opt[1] == 'n' || opt[2] != '\0')
		return (FALSE);
	return (TRUE);
}

/*
** - CHECK IF ARG IS A VALID NUMERIC VALUE
**   ac	->	main argc
**   av	->	main *argv[]
**   c	->	current arg position
*/

int		is_numeric(int ac, char **av, int i)
{
	if (i < ac && av[i][0] != '\0' && is_option(av[i]) == FALSE)
	{
		if (!ft_strisnumber(av[i], '\0'))
			return (log_this(NULL, LF_ERR, CWE_NOTNUM, av[i - 1], av[i]));
		if (av[i][0] == '-' || av[i][0] == '+')
			return (log_this(NULL, LF_ERR, CWE_SIGN,
							av[i - 1], av[i], av[i][0]));
		return (TRUE);
	}
	return (log_this(NULL, LF_ERR, CWE_NUMERIC, av[i - 1]));
}
