/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/14 04:28:11 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

/*
** -- PRINT A MEMORY ZONE IN A GIVEN FD
**    > Print the 'name' if given
**    > Print the len bytes of mem
**    > Print the cpu->pc in red, and the busy memory cells in green
*/

void	print_memory(char *buff, uint8_t *mem, uint32_t len, uint64_t pc)
{
	uint64_t	i;

	i = 0;
	while (i < len)
	{
		if (i == pc)
			ft_sprintf(buff, "{red}%2.2hhX{eoc}", mem[i]);
		else
			ft_sprintf(buff, mem[i] ? "{yellow}%2.2hhX{eoc}" : "%2.2hhX", mem[i]);
		buff += 2;
		i++;
	}
	buff[0] = '\n';
	buff[1] = '\0';
}
