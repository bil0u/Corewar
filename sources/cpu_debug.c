/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 03:59:00 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "instructions.h"

#include "cpu.h"
#include "libft.h"

void	print_memory(char *name, char *s, uint32_t len)
{
	if (name)
		ft_printf("{yellow}%s\t{cyan}%p{eoc}\t(%d bytes)\t", name, s, len);
	while (len--)
	{
		ft_printf(*s ? "{green}%2.2hhX{eoc}" : "%2.2hhX", *s);
		s++;
	}
	ft_printf("\n");
}

void	print_cpu(t_vcpu *cpu)
{
//	int		i;

	ft_printf("-- {cyan}CPU{eoc} --\n");
	ft_printf("{green}Carry:{eoc} %d\n", cpu->carry);
	ft_printf("{green}Program counter:{eoc} %p\n", cpu->pc);
	ft_printf("{green}Supported ops:{eoc} ");
/*	i = -1;
	while (++i < INSTR_NUMBER)
		if (CPU_OP_NO(i).name)
			ft_printf("%s ", CPU_OP_NO(i).name);
*/	print_memory("\nArgs buffers", (char *)cpu->args_buff, MAX_ARGS * sizeof(t_args));
	print_memory("Registers", cpu->registers, REG_LEN);
}
