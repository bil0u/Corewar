/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/15 16:20:41 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

/*
** -- PRINT MEMORY CONTENT (IN HEX)
**    > Print the cpu->pc in red, and the filled memory cells in yellow
*/

void	print_memory(t_vcpu *cpu)
{
	uint64_t	i;
	int			fd;

	fd = (get_logwin("mem"))->fd;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == cpu->pc)
			ft_dprintf(fd, "{red}%2.2u{eoc}", cpu->memory[i]);
		else if (cpu->memory[i])
			ft_dprintf(fd, "{yellow}%2.2u{eoc}", cpu->memory[i]);
		else
			ft_dprintf(fd, "%2.2u", cpu->memory[i]);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

/*
** -- PRINT REGISTERS CONTENT (IN HEX)
*/

void	print_registers(t_vcpu *cpu)
{
	uint64_t	i;
	int			fd;

	fd = (get_logwin("reg"))->fd;
	i = 0;
	while (i < (REG_NUMBER * REG_SIZE))
	{
		if (cpu->registers[i])
			ft_dprintf(fd, "{yellow}%2.2u{eoc}", cpu->registers[i]);
		else
			ft_dprintf(fd, "%2.2u", cpu->registers[i]);
		i++;
		if ((i % REG_SIZE) == 0 && i != (REG_NUMBER * REG_SIZE))
			ft_dprintf(fd, "{red}|{eoc}");
	}
	ft_putchar_fd('\n', fd);
}
