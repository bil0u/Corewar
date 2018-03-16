/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/16 02:51:37 by upopee           ###   ########.fr       */
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

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == cpu->pc)
			log_this("mem", 0, "{red}%2.2hhu{eoc}", cpu->memory[i]);
		else if (cpu->memory[i])
			log_this("mem", 0, "{yellow}%2.2hhu{eoc}", cpu->memory[i]);
		else
			log_this("mem", 0, "%2.2hhu", cpu->memory[i]);
		i++;
	}
	ft_putchar_fd('\n', get_winfd("mem"));
}

/*
** -- PRINT REGISTERS CONTENT (IN HEX)
*/

void	print_registers(t_vcpu *cpu)
{
	uint64_t	i;

	i = 0;
	while (i < (REG_NUMBER * REG_SIZE))
	{
		if (cpu->registers[i])
			log_this("reg", 0, "{yellow}%2.2hhu{eoc}", cpu->registers[i]);
		else
			log_this("reg", 0, "%2.2hhu", cpu->registers[i]);
		i++;
		if ((i % REG_SIZE) == 0 && i != (REG_NUMBER * REG_SIZE))
			log_this("reg", 0, "{red}|{eoc}");
	}
	ft_putchar_fd('\n', get_winfd("reg"));
}
