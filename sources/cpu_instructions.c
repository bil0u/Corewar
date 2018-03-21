/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/21 17:41:25 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"
#include "cpu_verbose.h"

int		live_instr(t_vcpu *cpu)			// NEEDS TO BE COMPLETED WHEN THE PSEUDO JOB CONTROL WILL BE DESIGNED
{
	uint32_t	player_no;

	secure_fetch(cpu->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_DIRSZ);
	player_no = cpu->op_args[0];
	log_this("ins", 0, P_ARG_DIR, 1, player_no);
	if (player_no && player_no < MAX_PLAYERS + 1)
	{
		log_this("ins", 0, OP_LIVE_OK, player_no);
	}
	else
	{
		log_this("ins", 0, OP_LIVE_KO, player_no);
	}
	return (ARG_DIRSZ);
}

int		load_instr(t_vcpu *cpu)
{
	uint8_t		r_dst;
	uint32_t	pc_tmp;
	int16_t		indirect;

	cpu->carry = 0;
	if ((r_dst = cpu->op_args[1]) != 0 && --r_dst <= REG_NUMBER)
	{
		if (((cpu->op_bytecode >> 6) & 0x03) == ARG_IND)
		{
			indirect = (int16_t)(cpu->op_args[0] & 0xFFFF) % IDX_MOD;
			pc_tmp = jump_to(cpu->pc, indirect);
			cpu->registers[r_dst] = cpu->memory[pc_tmp];
			log_this("ins", 0, OP_LD_IND, indirect, pc_tmp, r_dst + 1, cpu->memory[pc_tmp]);
		}
		else
		{
			cpu->registers[r_dst] = cpu->op_args[0];
			log_this("ins", 0, OP_LD_DIR, cpu->op_args[0], r_dst + 1);
		}
		cpu->carry = ((int)cpu->registers[r_dst] == 0);
	}
	else
		log_this("ins", 0, OP_LD_KO, cpu->op_args[1]);
	return (0);
}

int		store_instr(t_vcpu *cpu)
{
	uint32_t	pc_tmp;
	int16_t		indirect;
	uint8_t		r_dst;
	uint8_t		r_src;

	if ((r_src = cpu->op_args[0]) != 0 && --r_src < REG_NUMBER)
	{
		if (((cpu->op_bytecode >> 4) & 0x03) == ARG_IND)
		{
			indirect = (int16_t)(cpu->op_args[1] & 0xFFFF) % IDX_MOD;
			pc_tmp = jump_to(cpu->pc, indirect);
			secure_store(pc_tmp, cpu->memory, cpu->registers[r_src], REG_SIZE);
			log_this("ins", 0, OP_ST_IND, r_src + 1, indirect, pc_tmp, cpu->registers[r_src]);
		}
		else if ((r_dst = cpu->op_args[1]) != 0 && --r_dst < REG_NUMBER)
		{
			cpu->registers[r_dst] = cpu->registers[r_src];
			log_this("ins", 0, OP_ST_REG, r_src + 1, r_dst + 1, cpu->registers[r_src]);
		}
		else
			log_this("ins", 0, OP_ST_KO, cpu->op_args[1]);
	}
	else
	{
		log_this("ins", 0, OP_ST_KO, cpu->op_args[0]);
	}
	return (0);
}

int		add_instr(t_vcpu *cpu)
{
	uint32_t	*regs;
	uint8_t		r_a;
	uint8_t		r_b;
	uint8_t		r_dst;

	cpu->carry = 0;
	if ((r_dst = cpu->op_args[2]) != 0 && --r_dst < REG_NUMBER
		&& (r_a = cpu->op_args[0]) != 0 && --r_a < REG_NUMBER
		&& (r_b = cpu->op_args[1]) != 0 && --r_b < REG_NUMBER)
	{
		regs = cpu->registers;
		regs[r_dst] = (uint32_t)((int)(regs[r_a]) + (int)(regs[r_b]));
		cpu->carry = ((int)regs[r_dst] == 0);
		log_this("ins", 0, OP_ADD_OK, r_a + 1, r_b + 1, r_dst + 1, regs[r_dst], regs[r_dst]);
	}
	else
		log_this("ins", 0, OP_ADD_KO);
	return (0);
}

int		sub_instr(t_vcpu *cpu)
{
	uint32_t	*regs;
	uint8_t		r_a;
	uint8_t		r_b;
	uint8_t		r_dst;

	cpu->carry = 0;
	r_a = cpu->op_args[0];
	r_b = cpu->op_args[1];
	r_dst = cpu->op_args[2];
	if (r_dst != 0 && --r_dst < REG_NUMBER
		&& r_a != 0 && --r_a < REG_NUMBER
		&& r_b != 0 && --r_b < REG_NUMBER)
	{
		regs = cpu->registers;
		regs[r_dst] = (uint32_t)((int)(regs[r_a]) - (int)(regs[r_b]));
		cpu->carry = ((int)regs[r_dst] == 0);
		log_this("ins", 0, OP_SUB_OK, r_a + 1, r_b + 1, r_dst + 1, regs[r_dst], regs[r_dst]);
	}
	else
		log_this("ins", 0, OP_SUB_KO);
	return (0);
}

int		and_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		r_dst;

	cpu->carry = 0;
	if ((r_dst = cpu->op_args[2]) == 0 || r_dst-- > REG_NUMBER)
	{
		log_this("ins", 0, OP_AND_KO, cpu->op_args[2]);
		return (0);
	}
	i = -1;
	while (++i < 2 && (arg = cpu->op_args + i) != NULL)
	{
		if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
		{
			if (*arg == 0 || (*arg)-- > REG_NUMBER)
			{
				log_this("ins", 0, OP_AND_KO, *(cpu->op_args + i));
				return (0);
			}
			*arg = cpu->registers[*arg];
		}
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
		{
			*arg = (uint32_t)((int)*arg % IDX_MOD);
			*arg = cpu->memory[jump_to(cpu->pc, (int)*arg)];
		}
	}
	cpu->registers[r_dst] = cpu->op_args[0] & cpu->op_args[1];
	cpu->carry = ((int)cpu->registers[r_dst] == 0);
	log_this("ins", 0, OP_AND_OK, cpu->op_args[0], cpu->op_args[1], r_dst + 1, cpu->registers[r_dst]);
	return (0);
}

int		or_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		r_dst;

	cpu->carry = 0;
	if ((r_dst = cpu->op_args[2]) == 0 || r_dst-- > REG_NUMBER)
	{
		log_this("ins", 0, OP_OR_KO, cpu->op_args[2]);
		return (0);
	}
	i = -1;
	while (++i < 2 && (arg = cpu->op_args + i) != NULL)
	{
		if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
		{
			if (*arg == 0 || (*arg)-- > REG_NUMBER)
			{
				log_this("ins", 0, OP_OR_KO, *(cpu->op_args + i));
				return (0);
			}
			*arg = cpu->registers[*arg];
		}
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
		{
			*arg = (uint32_t)((int)*arg % IDX_MOD);
			*arg = cpu->memory[jump_to(cpu->pc, (int)*arg)];
		}
	}
	cpu->registers[r_dst] = cpu->op_args[0] | cpu->op_args[1];
	cpu->carry = ((int)cpu->registers[r_dst] == 0);
	log_this("ins", 0, OP_OR_OK, cpu->op_args[0], cpu->op_args[1], r_dst + 1, cpu->registers[r_dst]);
	return (0);
}

int		xor_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		r_dst;

	cpu->carry = 0;
	if ((r_dst = cpu->op_args[2]) == 0 || r_dst-- > REG_NUMBER)
	{
		log_this("ins", 0, OP_XOR_KO, cpu->op_args[2]);
		return (0);
	}
	i = -1;
	while (++i < 2 && (arg = cpu->op_args + i) != NULL)
	{
		if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
		{
			if (*arg == 0 || (*arg)-- > REG_NUMBER)
			{
				log_this("ins", 0, OP_XOR_KO, *(cpu->op_args + i));
				return (0);
			}
			*arg = cpu->registers[*arg];
		}
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
		{
			*arg = (uint32_t)((int)*arg % IDX_MOD);
			*arg = cpu->memory[jump_to(cpu->pc, (int)*arg)];
		}
	}
	cpu->registers[r_dst] = cpu->op_args[0] ^ cpu->op_args[1];
	cpu->carry = ((int)cpu->registers[r_dst] == 0);
	log_this("ins", 0, OP_XOR_OK, cpu->op_args[0], cpu->op_args[1], r_dst + 1, cpu->registers[r_dst]);
	return (0);
}

int		zjmp_instr(t_vcpu *cpu)
{
	int32_t		index;

	if (cpu->carry == 1)
	{
		secure_fetch(cpu->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_DIRSZ);
		index = (int32_t)cpu->op_args[0] % IDX_MOD;
		cpu->pc = jump_to(cpu->pc, (int)index);
		log_this("ins", 0, P_ARG_DIR, 1, cpu->op_args[0]);
		log_this("ins", 0, OP_ZJMP_OK, index);
		return (-OPBC_SIZE);
	}
	else
	{
		log_this("ins", 0, OP_ZJMP_KO);
		return (ARG_DIRSZ);
	}
}
