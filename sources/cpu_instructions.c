/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/20 18:05:06 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"

int		live_instr(t_vcpu *cpu)			// NEEDS TO BE COMPLETED WHEN THE PSEUDO JOB CONTROL WILL BE DESIGNED
{
	uint32_t	player_no;

	secure_fetch(cpu->pc + 1, cpu->memory, cpu->op_args, ARG_DIRSZ);
	player_no = cpu->op_args[0];
	log_this("ins", 0, "{green}Arg 1:{eoc} [DIRECT] | ({yellow}%#.2x{eoc})\n", player_no);
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
			log_this("ins", 0, "{green}Load:{eoc} (PC%+hd: %u) >> (Register %hhu)\t[{yellow}%#.2x{eoc}]\n",
						indirect, pc_tmp, reg_dst, cpu->memory[pc_tmp]);
		}
		else
		{
			cpu->registers[reg_dst - 1] = cpu->op_args[0];
			log_this("ins", 0, "{green}Load:{eoc} [{yellow}%#.2x{eoc}] >> (Register %hhu)\n",
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
			log_this("ins", 0, "{green}Store:{eoc} (Register %hhu) >> (PC%+hd: %u)\t[{yellow}%#.2x{eoc}]\n",
					reg_src, indirect, pc_tmp, cpu->registers[reg_src - 1]);
		}
		else if ((reg_dst = cpu->op_args[1]) != 0 && reg_dst - 1 < REG_NUMBER)
		{
			cpu->registers[reg_dst - 1] = cpu->registers[reg_src - 1];
			log_this("ins", 0, "{green}Store:{eoc} (Register %hhu) >> (Register %hhu)\t[{yellow}%#.2x{eoc}]\n",
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
		log_this("ins", 0, "{green}Add:{eoc} (Register %hhu) + (Register %hhu) >> (Register %hhu)\t[{yellow}%#.2x | %d{eoc}]\n",
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
		log_this("ins", 0, "{green}Sub:{eoc} (Register %hhu) + (Register %hhu) >> (Register %hhu)\t[{yellow}%#.2x | %d{eoc}]\n",
				reg_a, reg_b, reg_dst, cpu->registers[reg_dst - 1], cpu->registers[reg_dst - 1]);
	}
	else
		log_this("ins", 0, "{red}Sub:{eoc} One of the three parameters is invalid\n");
	return (0);
}

int		and_instr(t_vcpu *cpu)
{
	int			i;
	uint32_t	param[2];
	uint32_t	pc_tmp;
	uint8_t		reg_dst;

	cpu->carry = 0;
	reg_dst = cpu->op_args[2];
	if (reg_dst == 0 || reg_dst > REG_NUMBER)
	{
		log_this("ins", 0, "{red}And:{eoc} destination register not valid\n");
		return (0);
	}
	i = 0;
	while (i < 2)
	{
		if (((cpu->op_bytecode >> (6 - (i << 1))) & 0xFF) == ARG_REG)
		{
			if ((param[i] = cpu->op_args[i]) == 0 || param[i] > REG_NUMBER)
			{
				log_this("ins", 0, "{red}And:{eoc} register %hhu does not exists\n", param[i]);
				return (0);
			}
			param[i] = cpu->registers[param[i] - 1];
			ft_printf("%d\n", param[i]);
		}
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0xFF) == ARG_DIR)
			param[i] = cpu->op_args[i];
		else if (((cpu->op_bytecode >> (6 - (i << 1))) & 0xFF) == ARG_IND)
		{
			param[i] = (uint32_t)((int32_t)cpu->op_args[i] % IDX_MOD);
			pc_tmp = jump_to(cpu->pc, (int)param[i]);
			param[i] = cpu->memory[pc_tmp];
		}
		else
			ft_printf("Rien\n");
		i++;
	}
	cpu->registers[reg_dst - 1] = param[0] & param[1];
	cpu->carry = 1;
	log_this("ins", 0, "{green}And:{eoc} [{yellow}%#.2x{eoc}] & [{yellow}%#.2x{eoc}] >> (Register %hhu)\t[{yellow}%#.2x{eoc}]\n",
			param[0], param[1], reg_dst, cpu->registers[reg_dst - 1]);
	return (0);
}
