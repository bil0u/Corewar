/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/15 15:31:09 by upopee           ###   ########.fr       */
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

void	print_memory(uint8_t *mem, uint32_t len, uint64_t pc, int fd)
{
	uint64_t	i;

	i = 0;
	while (i < len)
	{
		if (i == pc)
			ft_dprintf(fd, "{red}%2.2u{eoc}", mem[i]);
		else
			ft_dprintf(fd, mem[i] != 0 ? "{yellow}%2.2u{eoc}" : "%2.2u", mem[i]);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
