/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/05 11:36:35 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

void	live_instr(uint8_t *memory, uint8_t *regs, uint8_t *carry, t_arg *args)
{
	(void)memory;
	(void)regs;
	(void)carry;
	ft_printf("Player %d is alive !\n", args[0].dir);
}

void	load_instr(uint8_t *memory, uint8_t *regs, uint8_t *carry, t_arg *args)
{
	(void)memory;
	(void)regs;
	(void)carry;
	(void)args;
}
