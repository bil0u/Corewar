/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:06:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 16:39:47 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

void	print_memory(char *name, uint8_t *s, uint32_t len, uint8_t *pc)
{
	if (name)
		ft_printf("{yellow}%s\t{cyan}%p{eoc}\t(%d bytes)\t", name, s, len);
	while (len--)
	{
		if (s == pc)
			ft_printf("{red}%2.2hhX{eoc}", *s);
		else
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
*/	print_memory("\nArgs buffers", (uint8_t *)cpu->args_buff, MAX_ARGS * sizeof(t_arg), NULL);
	print_memory("Registers", cpu->registers, REG_LEN, NULL);
}
