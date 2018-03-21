/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/21 00:46:20 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

/*
** -- PRINT MEMORY CONTENT (IN HEX)
**    > Print the cpu->pc in red, and the filled memory cells in yellow
*/

void	print_memory(t_vcpu *cpu, char clean)
{
	char		buff[4096];
	uint32_t	i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	if (clean)
		clear_window("mem");
	while (i < MEM_SIZE)
	{
		if (i == cpu->pc)
			ret += ft_sprintf(buff + ret, "{yellow}%2.2hhx{eoc}", cpu->memory[i]);
		else if (cpu->memory[i])
			ret += ft_sprintf(buff + ret, "{cyan}%2.2hhx{eoc}", cpu->memory[i]);
		else
			ret += ft_sprintf(buff + ret, "%2.2hhx", cpu->memory[i]);
		++i;
	}
	log_this("mem", 0, buff);
	ft_putchar_fd('\n', get_winfd("mem"));
}

/*
** -- PRINT REGISTERS CONTENT (IN HEX)
*/

void	print_registers(t_vcpu *cpu, char clean)
{
	char		buff[4096];
	uint8_t		i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	if (clean)
		clear_window("reg");
	while (i < REG_NUMBER)
	{
		if (cpu->registers[i])
			ret += ft_sprintf(buff + ret, "{yellow}%8.8x{eoc}", cpu->registers[i]);
		else
			ret += ft_sprintf(buff + ret, "%8.8x", cpu->registers[i]);
		i++;
		if (i != REG_NUMBER)
			ret += ft_sprintf(buff + ret, "{red}|{eoc}");
	}
	log_this("reg", 0, buff);
	ft_putchar_fd('\n', get_winfd("reg"));
}
