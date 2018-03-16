/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/16 03:23:32 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"

void	live_instr(t_vcpu *cpu)			// NEEDS TO BE COMPLETED WHEN THE PSEUDO JOB CONTROL WILL BE DESIGNED
{
	uint32_t	player_no;

	secure_fetch(&cpu->pc, cpu->memory, cpu->op_args, ARG_DIRSZ);
	player_no = cpu->op_args[0];
	if (player_no && player_no < MAX_PLAYERS + 1)
	{
		log_this("ins", 0, "{green}Live: Player %u is alive !{eoc}\n", player_no);
	}
	else
	{
		log_this("ins", LF_ERR, "{red}Live: Bad player no %u{eoc}\n", player_no);
	}
}


void	load_instr(t_vcpu *cpu)
{
	uint8_t		reg_no;
	int			value;

	reg_no = cpu->op_args[1];
	if (reg_no < REG_NUMBER)
	{
		value = (int)cpu->op_args[0];
		if ((cpu->op_bytecode & 0x00FF0000) == T_IND)
			value = cpu->memory[jump_to(cpu->pc, value % IDX_MOD)];
		cpu->registers[reg_no] = (uint32_t)value;
		cpu->carry = 1;
		log_this("ins", LF_ERR, "{green}Load: register[%hhu] = %u{eoc}\n", reg_no, value);
	}
	else
	{
		cpu->carry = 0;
		log_this("ins", LF_ERR, "{red}Load: register[%hhu] does not exists{eoc}\n", reg_no);
	}
}
