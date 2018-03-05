/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/05 04:50:00 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

void	print_memory(char *name, uint8_t *mem, uint32_t len, uint64_t pc)
{
	uint64_t	i;

	i = 0;
	if (name)
		ft_printf("{yellow}%s\t{cyan}%p{eoc}\t(%d bytes)\t", name, mem, len);
	while (i < len)
	{
		if (i == pc)
			ft_printf("{red}%2.2hhX{eoc}", mem[i]);
		else
			ft_printf(mem[i] ? "{green}%2.2hhX{eoc}" : "%2.2hhX", mem[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_cpu(t_vcpu *cpu)
{
//	int		i;

	ft_printf("-- {cyan}CPU{eoc} --\n");
	ft_printf("{green}Carry:{eoc} %hhu\n", cpu->carry);
	ft_printf("{green}Program counter index:{eoc} %lu\n", cpu->pc);
	ft_printf("{green}Supported ops:{eoc} ");
/*	i = -1;
	while (++i < INSTR_NUMBER)
		if (g_op_set[i].name)
			ft_printf("%s ", g_op_set[i].name);
*/	print_memory("\nArgs buffers", (uint8_t *)cpu->args_buff, MAX_ARGS * sizeof(t_arg), MAX_ARGS * sizeof(t_arg) + 1);
	print_memory("Registers", cpu->registers, REG_LEN, REG_LEN + 1);
}
