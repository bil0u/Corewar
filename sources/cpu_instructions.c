/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/21 01:43:17 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"

int		live_instr(t_vcpu *cpu)			// NEEDS TO BE COMPLETED WHEN THE PSEUDO JOB CONTROL WILL BE DESIGNED
{
	uint32_t	player_no;

	secure_fetch(cpu->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_DIRSZ);
	player_no = cpu->op_args[0];
	log_this("ins", 0, "{green}Arg 1:{eoc} [DIRECT] | ({yellow}0x%.2x{eoc})\n", player_no);
	if (player_no && player_no < MAX_PLAYERS + 1)
	{
		log_this("ins", 0, "{green}Live:{eoc} Player %u is alive !\n", player_no);
	}
	else
	{
		log_this("ins", 0, "{red}Live:{eoc} Player no %u does not exist\n", player_no);
	}
	return (ARG_DIRSZ);
}

int		load_instr(t_vcpu *cpu)
{
	uint8_t		reg_dst;
	uint32_t	pc_tmp;
	int16_t		indirect;

	cpu->carry = 0;
	reg_dst = cpu->op_args[1];
	if (reg_dst != 0 && reg_dst <= REG_NUMBER)
	{
		if (((cpu->op_bytecode >> 6) & 0x03) == ARG_IND)
		{
			indirect = (int16_t)(cpu->op_args[0] & 0xFFFF) % IDX_MOD;
			pc_tmp = jump_to(cpu->pc, indirect);
			cpu->registers[reg_dst - 1] = cpu->memory[pc_tmp];
			log_this("ins", 0, "{green}Load:{eoc} (PC%+hd: %u) >> (Register %hhu)\t[{yellow}0x%.2x{eoc}]\n",
						indirect, pc_tmp, reg_dst, cpu->memory[pc_tmp]);
		}
		else
		{
			cpu->registers[reg_dst - 1] = cpu->op_args[0];
			log_this("ins", 0, "{green}Load:{eoc} [{yellow}0x%.2x{eoc}] >> (Register %hhu)\n",
					cpu->op_args[0], reg_dst);
		}
		cpu->carry = 1;
	}
	else
		log_this("ins", 0, "{red}Load:{eoc} register %hhu does not exists\n", reg_dst);
	return (0);
}

int		store_instr(t_vcpu *cpu)
{
	uint32_t	pc_tmp;
	int16_t		indirect;
	uint8_t		reg_dst;
	uint8_t		reg_src;

	reg_src = cpu->op_args[0];
	if (reg_src != 0 && reg_src - 1 < REG_NUMBER)
	{
		if (((cpu->op_bytecode >> 4) & 0x03) == ARG_IND)
		{
			indirect = (int16_t)(cpu->op_args[1] & 0xFFFF) % IDX_MOD;
			pc_tmp = jump_to(cpu->pc, indirect);
			secure_store(pc_tmp, cpu->memory, cpu->registers[reg_src - 1], REG_SIZE);
			log_this("ins", 0, "{green}Store:{eoc} (Register %hhu) >> (PC%+hd: %u)\t[{yellow}0x%.2x{eoc}]\n",
					reg_src, indirect, pc_tmp, cpu->registers[reg_src - 1]);
		}
		else if ((reg_dst = cpu->op_args[1]) != 0 && reg_dst - 1 < REG_NUMBER)
		{
			cpu->registers[reg_dst - 1] = cpu->registers[reg_src - 1];
			log_this("ins", 0, "{green}Store:{eoc} (Register %hhu) >> (Register %hhu)\t[{yellow}0x%.2x{eoc}]\n",
					reg_src, reg_dst, cpu->registers[reg_src - 1]);
		}
		else
			log_this("ins", 0, "{red}Store:{eoc} register %hhu does not exists\n", reg_dst);
	}
	else
	{
		log_this("ins", 0, "{red}Store:{eoc} register %hhu does not exists\n", reg_src);
	}
	return (0);
}

int		add_instr(t_vcpu *cpu)
{
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	cpu->carry = 0;
	reg_a = cpu->op_args[0];
	reg_b = cpu->op_args[1];
	reg_dst = cpu->op_args[2];
	if (reg_dst != 0 && reg_dst - 1 < REG_NUMBER
		&& reg_a != 0 && reg_a - 1 < REG_NUMBER
		&& reg_b != 0 && reg_b - 1 < REG_NUMBER)
	{
		cpu->registers[reg_dst - 1] =
			(uint32_t)((int32_t)(cpu->registers[reg_a - 1])
					+ (int32_t)(cpu->registers[reg_b - 1]));
		cpu->carry = 1;
		log_this("ins", 0, "{green}Add:{eoc} (Register %hhu) + (Register %hhu) >> (Register %hhu)\t[{yellow}0x%.2x | %d{eoc}]\n",
				reg_a, reg_b, reg_dst, cpu->registers[reg_dst - 1], cpu->registers[reg_dst - 1]);
	}
	else
		log_this("ins", 0, "{red}Add:{eoc} One of the three parameters is invalid\n");
	return (0);
}

int		sub_instr(t_vcpu *cpu)
{
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	cpu->carry = 0;
	reg_a = cpu->op_args[0];
	reg_b = cpu->op_args[1];
	reg_dst = cpu->op_args[2];
	if (reg_dst != 0 && reg_dst - 1 < REG_NUMBER
		&& reg_a != 0 && reg_a - 1 < REG_NUMBER
		&& reg_b != 0 && reg_b - 1 < REG_NUMBER)
	{
		cpu->registers[reg_dst - 1] =
			(uint32_t)((int32_t)(cpu->registers[reg_a - 1])
					- (int32_t)(cpu->registers[reg_b - 1]));
		cpu->carry = 1;
		log_this("ins", 0, "{green}Sub:{eoc} (Register %hhu) + (Register %hhu) >> (Register %hhu)\t[{yellow}0x%.2x | %d{eoc}]\n",
				reg_a, reg_b, reg_dst, cpu->registers[reg_dst - 1], cpu->registers[reg_dst - 1]);
	}
	else
		log_this("ins", 0, "{red}Sub:{eoc} One of the three parameters is invalid\n");
	return (0);
}

int		and_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) == 0 || reg_dst > REG_NUMBER)
	{
		log_this("ins", 0, "{red}And:{eoc} register %hhu does not exists\n", reg_dst);
		return (0);
	}
	i = -1;
	while (++i < 2 && (arg = cpu->op_args + i) != NULL)
	{
		if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
		{
			if (*arg == 0 || *arg > REG_NUMBER)
			{
				log_this("ins", 0, "{red}And:{eoc} register %hhu does not exists\n", *arg);
				return (0);
			}
			*arg = cpu->registers[*arg - 1];
		}
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
		{
			*arg = (uint32_t)((int32_t)*arg % IDX_MOD);
			*arg = cpu->memory[jump_to(cpu->pc, (int)*arg)];
		}
	}
	cpu->registers[reg_dst - 1] = cpu->op_args[0] & cpu->op_args[1];
	cpu->carry = 1;
	log_this("ins", 0, "{green}And:{eoc} [{yellow}0x%.2x{eoc}] & [{yellow}0x%.2x{eoc}] >> (Register %hhu)\t[{yellow}0x%.2x{eoc}]\n",
			cpu->op_args[0], cpu->op_args[1], reg_dst, cpu->registers[reg_dst - 1]);
	return (0);
}

int		or_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) == 0 || reg_dst > REG_NUMBER)
	{
		log_this("ins", 0, "{red}Or:{eoc} register %hhu does not exists\n", reg_dst);
		return (0);
	}
	i = -1;
	while (++i < 2 && (arg = cpu->op_args + i) != NULL)
	{
		if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
		{
			if (*arg == 0 || *arg > REG_NUMBER)
			{
				log_this("ins", 0, "{red}Or:{eoc} register %hhu does not exists\n", *arg);
				return (0);
			}
			*arg = cpu->registers[*arg - 1];
		}
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
		{
			*arg = (uint32_t)((int32_t)*arg % IDX_MOD);
			*arg = cpu->memory[jump_to(cpu->pc, (int)*arg)];
		}
	}
	cpu->registers[reg_dst - 1] = cpu->op_args[0] | cpu->op_args[1];
	cpu->carry = 1;
	log_this("ins", 0, "{green}Or:{eoc} [{yellow}0x%.2x{eoc}] | [{yellow}0x%.2x{eoc}] >> (Register %hhu)\t[{yellow}0x%.2x{eoc}]\n",
			cpu->op_args[0], cpu->op_args[1], reg_dst, cpu->registers[reg_dst - 1]);
	return (0);
}

int		xor_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	*arg;
	uint8_t		reg_dst;

	cpu->carry = 0;
	if ((reg_dst = cpu->op_args[2]) == 0 || reg_dst > REG_NUMBER)
	{
		log_this("ins", 0, "{red}Xor:{eoc} register %hhu does not exists\n", reg_dst);
		return (0);
	}
	i = -1;
	while (++i < 2 && (arg = cpu->op_args + i) != NULL)
	{
		if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_REG)
		{
			if (*arg == 0 || *arg > REG_NUMBER)
			{
				log_this("ins", 0, "{red}Xor:{eoc} register %hhu does not exists\n", *arg);
				return (0);
			}
			*arg = cpu->registers[*arg - 1];
		}
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0x03) == ARG_IND)
		{
			*arg = (uint32_t)((int32_t)*arg % IDX_MOD);
			*arg = cpu->memory[jump_to(cpu->pc, (int)*arg)];
		}
	}
	cpu->registers[reg_dst - 1] = cpu->op_args[0] ^ cpu->op_args[1];
	cpu->carry = 1;
	log_this("ins", 0, "{green}Xor:{eoc} [{yellow}0x%.2x{eoc}] ^ [{yellow}0x%.2x{eoc}] >> (Register %hhu)\t[{yellow}0x%.2x{eoc}]\n",
			cpu->op_args[0], cpu->op_args[1], reg_dst, cpu->registers[reg_dst - 1]);
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
		log_this("ins", 0, "{green}Arg 1:{eoc} [DIRECT] | ({yellow}0x%.2x{eoc})\n", cpu->op_args[0]);
		log_this("ins", 0, "{green}Zjump:{eoc} [Carry = 1] moving PC at {yellow}%+d{eoc}\n", index);
		return (-OPBC_SIZE);
	}
	else
	{
		log_this("ins", 0, "{red}Zjump:{eoc} [Carry = 0] continuing to next op\n");
		return (ARG_DIRSZ);
	}
}
