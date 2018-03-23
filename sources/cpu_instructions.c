/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/23 01:56:08 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"
#include "cpu_verbose.h"

int		live_instr(t_vcpu *cpu)			// NEEDS TO BE COMPLETED
{
	uint32_t	playereg_no;

	secure_fetch(cpu->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_DIRSZ);
	playereg_no = cpu->op_args[0];
	log_this("ins", 0, P_ARG_DIR, 1, playereg_no, playereg_no);
	if (playereg_no && playereg_no < MAX_PLAYERS + 1)
	{
		log_this("ins", 0, LIVE_OK, playereg_no);
	}
	else
	{
		log_this("ins", 0, LIVE_KO, playereg_no);
	}
	return (ARG_DIRSZ);
}

int		load_instr(t_vcpu *cpu)
{
	uint32_t	data;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[1]) != 0 && --reg_dst <= REG_NUMBER)
	{
		data = cpu->op_args[0];
		if (((cpu->op_bytecode >> 6) & 0x03) == ARG_IND)
		{
			cpu->registers[reg_dst] = cpu->memory[data];
			log_this("ins", 0, LD_IND, data, reg_dst + 1, cpu->memory[data]);
		}
		else
		{
			cpu->registers[reg_dst] = data;
			log_this("ins", 0, LD_DIR, data, reg_dst + 1);
		}
		cpu->carry = ((int)cpu->registers[reg_dst] == 0);
	}
	else
		log_this("ins", 0, LD_KO, cpu->op_args[1]);
	return (0);
}

int		store_instr(t_vcpu *cpu)
{
	uint32_t	data;
	uint8_t		reg_src;

	if ((reg_src = cpu->op_args[0]) != 0 || --reg_src < REG_NUMBER)
	{
		data = cpu->op_args[1];
		if (((cpu->op_bytecode >> 4) & 0x03) == ARG_IND)
		{
			secure_store(data, cpu->memory, cpu->registers[reg_src], REG_SIZE);
			log_this("ins", 0, ST_IND, reg_src + 1, data, cpu->registers[reg_src]);
		}
		else if (data != 0 && --data < REG_NUMBER)
		{
			cpu->registers[data] = cpu->registers[reg_src];
			log_this("ins", 0, ST_REG, reg_src + 1, data + 1, cpu->registers[reg_src]);
		}
		else
			log_this("ins", 0, ST_KO, cpu->op_args[1]);

	}
	else
		log_this("ins", 0, ST_KO, cpu->op_args[0]);
	return (0);
}

int		add_instr(t_vcpu *cpu)
{
	uint32_t	*r;
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) != 0 && --reg_dst < REG_NUMBER
		&& (reg_a = cpu->op_args[0]) != 0 && --reg_a < REG_NUMBER
		&& (reg_b = cpu->op_args[1]) != 0 && --reg_b < REG_NUMBER)
	{
		r = cpu->registers;
		r[reg_dst] = (uint32_t)((int)(r[reg_a]) + (int)(r[reg_b]));
		cpu->carry = ((int)r[reg_dst] == 0);
		log_this("ins", 0, ADD_OK, reg_a + 1, reg_b + 1, reg_dst + 1,
												r[reg_dst], r[reg_dst]);
	}
	else
		log_this("ins", 0, ADD_KO);
	return (0);
}

int		sub_instr(t_vcpu *cpu)
{
	uint32_t	*r;
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) != 0 && --reg_dst < REG_NUMBER
		&& (reg_a = cpu->op_args[0]) != 0 && --reg_a < REG_NUMBER
		&& (reg_b = cpu->op_args[1]) != 0 && --reg_b < REG_NUMBER)
	{
		r = cpu->registers;
		r[reg_dst] = (uint32_t)((int)(r[reg_a]) - (int)(r[reg_b]));
		cpu->carry = ((int)r[reg_dst] == 0);
		log_this("ins", 0, SUB_OK, reg_a + 1, reg_b + 1, reg_dst + 1,
												r[reg_dst], r[reg_dst]);
	}
	else
		log_this("ins", 0, SUB_KO);
	return (0);
}

int		and_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		i = -1;
		while (++i < 2 && (arg = cpu->op_args + i) != NULL)
			if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
				if (*arg != 0 && --(*arg) < REG_NUMBER)
					*arg = cpu->registers[*arg];
				else
				{
					log_this("ins", 0, AND_KO, *(cpu->op_args + i));
					return (0);
				}
			else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
				*arg = cpu->memory[*arg];
		cpu->registers[reg_dst] = cpu->op_args[0] & cpu->op_args[1];
		cpu->carry = ((int)cpu->registers[reg_dst] == 0);
		log_this("ins", 0, AND_OK, cpu->op_args[0], cpu->op_args[1], reg_dst + 1, cpu->registers[reg_dst]);
	}
	else
		log_this("ins", 0, AND_KO, cpu->op_args[2]);
	return (0);
}

int		or_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		i = -1;
		while (++i < 2 && (arg = cpu->op_args + i) != NULL)
			if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
				if (*arg != 0 && --(*arg) < REG_NUMBER)
					*arg = cpu->registers[*arg];
				else
				{
					log_this("ins", 0, OR_KO, *(cpu->op_args + i));
					return (0);
				}
			else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
				*arg = cpu->memory[*arg];
		cpu->registers[reg_dst] = cpu->op_args[0] | cpu->op_args[1];
		cpu->carry = ((int)cpu->registers[reg_dst] == 0);
		log_this("ins", 0, OR_OK, cpu->op_args[0], cpu->op_args[1], reg_dst + 1, cpu->registers[reg_dst]);
	}
	else
		log_this("ins", 0, OR_KO, cpu->op_args[2]);
	return (0);
}

int		xor_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		i = -1;
		while (++i < 2 && (arg = cpu->op_args + i) != NULL)
			if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
				if (*arg != 0 && --(*arg) < REG_NUMBER)
					*arg = cpu->registers[*arg];
				else
				{
					log_this("ins", 0, XOR_KO, *(cpu->op_args + i));
					return (0);
				}
			else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
				*arg = cpu->memory[*arg];
		cpu->registers[reg_dst] = cpu->op_args[0] ^ cpu->op_args[1];
		cpu->carry = ((int)cpu->registers[reg_dst] == 0);
		log_this("ins", 0, XOR_OK, cpu->op_args[0], cpu->op_args[1], reg_dst + 1, cpu->registers[reg_dst]);
	}
	else
		log_this("ins", 0, XOR_KO, cpu->op_args[2]);
	return (0);
}

int		zjmp_instr(t_vcpu *cpu)
{
	if (cpu->carry == 1)
	{
		secure_fetch(cpu->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_DIRSZ);
		log_this("ins", 0, P_ARG_DIR, 1, cpu->op_args[0], cpu->op_args[0]);
		cpu->pc = jump_to(cpu->pc, (int)(cpu->op_args[0] & 0xFFFF) % IDX_MOD);
		log_this("ins", 0, ZJMP_OK, (int)cpu->op_args[0] % IDX_MOD, cpu->pc);
		return (-OPBC_SIZE);
	}
	else
	{
		log_this("ins", 0, ZJMP_KO);
		return (ARG_DIRSZ);
	}
}
