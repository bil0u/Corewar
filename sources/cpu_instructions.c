/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/15 20:34:39 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"

void	live_instr(t_vcpu *cpu)
{
	int			fd;

	fd = (get_logwin("ins"))->fd;

	secure_fetch(&cpu->pc, cpu->memory, cpu->op_args, ARG_DIRSZ);
	ft_dprintf(fd, "Player %d is alive !\n", cpu->op_args[0]);
}

void	load_instr(t_vcpu *cpu)
{
	uint8_t		reg_no;
	int			value;

	int			fd;

	fd = (get_logwin("ins"))->fd;

	reg_no = cpu->op_args[1];
	if (reg_no < REG_NUMBER)
	{
		value = (int)cpu->op_args[0];
		if ((cpu->op_bytecode & 0x00FF0000) == T_IND)
			value = cpu->memory[jump_to(cpu->pc, value % IDX_MOD)];
		cpu->registers[reg_no] = (uint32_t)value;
		cpu->carry = 1;
		ft_dprintf(fd, "Load: register[%hhu] = %u\n", reg_no, value);
	}
	else
	{
		cpu->carry = 0;
		ft_dprintf(fd, "Load: register[%hhu] does not exists\n", reg_no);
	}
}
