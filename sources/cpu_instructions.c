/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/04/11 17:34:49 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "cpu.h"
#include "cpu_verbose.h"

int		live_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	player_no;

	secure_fetch(cpu->pc[0] + OPBC_SIZE, cpu->memory, dat->op_args, ARG_DIRSZ);
	player_no = dat->op_args[0] - REG_MAXVALUE + 1;
	log_this("ins", 0, P_ARG_DIR, 1, player_no);
	if (player_no && player_no < MAX_PLAYERS + 1)
	{
		dat->last_live[0] = cpu->tick;
		dat->last_alive[0] = player_no & 0xFF;
		log_this("ins", 0, LIVE_OK, player_no);
	}
	else
		log_this("ins", 0, LIVE_KO, player_no);
	return (ARG_DIRSZ);
}

int		ld_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		reg_dst;

	cpu->carry[0] = 0;
	if ((reg_dst = dat->op_args[1]) != 0 && --reg_dst < REG_NUMBER)
	{
		data = dat->op_args[0];
		r = cpu->registers;
		if (((dat->op_bytecode >> 6) & 0x03) == ARG_IND)
		{
			secure_fetch(data, cpu->memory, r + reg_dst, REG_SIZE);
			log_this("ins", 0, LD_IND, data, r[reg_dst], reg_dst + 1);
		}
		else
		{
			r[reg_dst] = data;
			log_this("ins", 0, LD_DIR, data, reg_dst + 1);
		}
		cpu->carry[0] = (r[reg_dst] == 0);
	}
	else
		log_this("ins", 0, LD_KO, dat->op_args[1]);
	return (0);
}

int		st_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		reg_src;

	if ((reg_src = dat->op_args[0]) != 0 || --reg_src < REG_NUMBER)
	{
		r = cpu->registers;
		data = dat->op_args[1];
		if (((dat->op_bytecode >> 4) & 0x03) == ARG_IND)
		{
			secure_store(data, cpu->memory, r[reg_src], REG_SIZE);
			log_this("ins", 0, ST_IND, reg_src + 1, r[reg_src], data);
		}
		else if (data != 0 && --data < REG_NUMBER)
		{
			r[data] = r[reg_src];
			log_this("ins", 0, ST_REG, reg_src + 1, r[reg_src], data + 1);
		}
		else
			log_this("ins", 0, ST_KO, dat->op_args[1]);
	}
	else
		log_this("ins", 0, ST_KO, dat->op_args[0]);
	return (0);
}

int		add_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*r;
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	cpu->carry[0] = 0;
	if ((reg_dst = dat->op_args[2]) != 0 && --reg_dst < REG_NUMBER
		&& (reg_a = dat->op_args[0]) != 0 && --reg_a < REG_NUMBER
		&& (reg_b = dat->op_args[1]) != 0 && --reg_b < REG_NUMBER)
	{
		r = cpu->registers;
		r[reg_dst] = (uint32_t)((int)(r[reg_a]) + (int)(r[reg_b]));
		cpu->carry[0] = (r[reg_dst] == 0);
		log_this("ins", 0, ADD_OK, ++reg_a, ++reg_b, r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, ADD_KO);
	return (0);
}

int		sub_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*r;
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	cpu->carry[0] = 0;
	if ((reg_dst = dat->op_args[2]) != 0 && --reg_dst < REG_NUMBER
		&& (reg_a = dat->op_args[0]) != 0 && --reg_a < REG_NUMBER
		&& (reg_b = dat->op_args[1]) != 0 && --reg_b < REG_NUMBER)
	{
		r = cpu->registers;
		r[reg_dst] = (uint32_t)((int)(r[reg_a]) - (int)(r[reg_b]));
		cpu->carry[0] = (r[reg_dst] == 0);
		log_this("ins", 0, SUB_OK, ++reg_a, ++reg_b, r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, SUB_KO);
	return (0);
}

int		and_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		reg_dst;

	cpu->carry[0] = 0;
	arg = dat->op_args;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		r = cpu->registers;
		if (decode_arg(cpu, (dat->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, AND_KO, arg[0]));
		if (decode_arg(cpu, (dat->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, AND_KO, arg[1]));
		r[reg_dst] = arg[0] & arg[1];
		cpu->carry[0] = (r[reg_dst] == 0);
		log_this("ins", 0, AND_OK, arg[0], arg[1], r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, AND_KO, arg[2]);
	return (0);
}

int		or_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		reg_dst;

	cpu->carry[0] = 0;
	arg = dat->op_args;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		r = cpu->registers;
		if (decode_arg(cpu, (dat->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, OR_KO, arg[0]));
		if (decode_arg(cpu, (dat->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, OR_KO, arg[1]));
		r[reg_dst] = arg[0] | arg[1];
		cpu->carry[0] = (r[reg_dst] == 0);
		log_this("ins", 0, OR_OK, arg[0], arg[1], r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, OR_KO, arg[2]);
	return (0);
}

int		xor_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		reg_dst;

	cpu->carry[0] = 0;
	arg = dat->op_args;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		r = cpu->registers;
		if (decode_arg(cpu, (dat->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, XOR_KO, arg[0]));
		if (decode_arg(cpu, (dat->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, XOR_KO, arg[1]));
		r[reg_dst] = arg[0] ^ arg[1];
		cpu->carry[0] = (r[reg_dst] == 0);
		log_this("ins", 0, XOR_OK, arg[0], arg[1], r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, XOR_KO, arg[2]);
	return (0);
}

int		zjmp_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	int16_t		restricted;

	if (cpu->carry[0] == 1)
	{
		secure_fetch(cpu->pc[0] + OPBC_SIZE, cpu->memory,
										dat->op_args, ARG_INDSZ);
		restricted = (int16_t)(dat->op_args[0] & 0xFFFF) % IDX_MOD;
		cpu->pc[0] = jump_to(cpu->pc[0], restricted);
		log_this("ins", 0, P_ARG_IND, 1, (int16_t)(dat->op_args[0] & 0xFFFF));
		log_this("ins", 0, P_IND_MOD, restricted);
		log_this("ins", 0, ZJMP_OK, restricted, cpu->pc[0]);
		return (-OPBC_SIZE);
	}
	else
	{
		log_this("ins", 0, ZJMP_KO);
		return (ARG_INDSZ);
	}
}

int		ldi_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*arg;
	uint32_t	data;
	uint8_t		reg_dst;

	arg = dat->op_args;
	cpu->carry[0] = 0;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		if (decode_arg(cpu, (dat->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, LDI_KO, arg[0]));
		if (decode_arg(cpu, (dat->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, LDI_KO, arg[1]));
		data = ((int)arg[0] + (int)arg[1]) % IDX_MOD;
		data = jump_to(cpu->pc[0], (int)data);
		secure_fetch(data, cpu->memory, cpu->registers + reg_dst, REG_SIZE);
		cpu->carry[0] = (cpu->registers[reg_dst] == 0);
		log_this("ins", 0, LDI_OK, arg[0], arg[1],
						data, reg_dst + 1, cpu->registers[reg_dst]);
	}
	else
		log_this("ins", 0, LDI_KO, arg[2]);
	return (0);
}

int		sti_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*arg;
	uint32_t	data;
	uint8_t		reg_src;

	arg = dat->op_args;
	if ((reg_src = arg[0]) != 0 && --reg_src < REG_NUMBER)
	{
		if (decode_arg(cpu, (dat->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, LDI_KO, arg[1]));
		if (decode_arg(cpu, (dat->op_bytecode >> 2) & 0x03, arg + 2) == FAILURE)
			return (log_this("ins", 0, LDI_KO, arg[2]));
		data = ((int)arg[1] + (int)arg[2]) % IDX_MOD;
		data = jump_to(cpu->pc[0], (int)data);
		secure_store(data, cpu->memory, cpu->registers[reg_src], REG_SIZE);
		log_this("ins", 0, STI_OK, reg_src + 1, arg[1],
					arg[2], data, cpu->registers[reg_src]);
	}
	else
		log_this("ins", 0, STI_KO, arg[0]);
	return (0);
}

int		fork_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	t_process	child;

	dat->nb_processes++;
	dat->tot_processes++;
	secure_fetch(cpu->pc[0] + OPBC_SIZE, cpu->memory, dat->op_args, ARG_INDSZ);
	dat->op_args[0] = (uint32_t)(((int32_t)dat->op_args[0]) % IDX_MOD);
	child.pc = jump_to(cpu->pc[0], (int32_t)dat->op_args[0]);
	child.pid = dat->tot_processes[0];
	child.player_no = dat->curr_player;
	child.timer = 0;
	child.last_live = cpu->tick;
	child.carry = cpu->carry[0];
	ft_memcpy(child.registers, cpu->registers, REG_LEN);
	dat->child_process = ft_lstnew(&child, sizeof(child));
	return (ARG_INDSZ);
}

int		lld_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		reg_dst;

	cpu->carry[0] = 0;
	if ((reg_dst = dat->op_args[1]) != 0 && --reg_dst < REG_NUMBER)
	{
		data = dat->op_args[0];
		r = cpu->registers;
		if (((dat->op_bytecode >> 6) & 0x03) == ARG_IND)
		{
			secure_fetch(data, cpu->memory, r + reg_dst, REG_SIZE);
			log_this("ins", 0, LLD_IND, data, reg_dst + 1, r[reg_dst]);
			ft_printf("%d\n", reg_dst);
		}
		else
		{
			r[reg_dst] = data;
			log_this("ins", 0, LLD_DIR, data, reg_dst + 1);
		}
		cpu->carry[0] = (r[reg_dst] == 0);
	}
	else
		log_this("ins", 0, LLD_KO, dat->op_args[1]);
	return (0);
}

int		lldi_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint32_t	*arg;
	uint32_t	data;
	uint8_t		reg_dst;

	arg = dat->op_args;
	cpu->carry[0] = 0;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		if (decode_arg(cpu, (dat->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, LLDI_KO, arg[0]));
		if (decode_arg(cpu, (dat->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, LLDI_KO, arg[1]));
		data = ((int)arg[0] + (int)arg[1]);
		data = jump_to(cpu->pc[0], (int)data);
		secure_fetch(data, cpu->memory, cpu->registers + reg_dst, REG_SIZE);
		cpu->carry[0] = (cpu->registers[reg_dst] == 0);
		log_this("ins", 0, LLDI_OK, arg[0], arg[1],
						data, reg_dst + 1, cpu->registers[reg_dst]);
	}
	else
		log_this("ins", 0, LLDI_KO, arg[2]);
	return (0);
}

int		lfork_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	t_process	child;

	dat->nb_processes++;
	dat->tot_processes++;
	secure_fetch(cpu->pc[0] + OPBC_SIZE, cpu->memory, dat->op_args, ARG_INDSZ);
	child.pc = jump_to(cpu->pc[0], (int32_t)dat->op_args[0]);
	child.pid = dat->tot_processes[0];
	child.player_no = dat->curr_player;
	child.timer = 0;
	child.last_live = cpu->tick;
	child.carry = cpu->carry[0];
	ft_memcpy(child.registers, cpu->registers, REG_LEN);
	dat->child_process = ft_lstnew(&child, sizeof(child));
	return (ARG_INDSZ);
}

int		aff_instr(t_vcpu *cpu, t_vcpudata *dat)
{
	uint8_t		reg_src;
	char		to_print;

	if ((reg_src = dat->op_args[0]) != 0 && --reg_src < REG_NUMBER)
	{
		to_print = cpu->registers[reg_src] & 0xFF;
		write(1, &to_print, 1);
		log_this("ins", 0, AFF_OK, to_print, reg_src + 1);
	}
	else
		log_this("ins", 0, AFF_KO, dat->op_args[0]);
	return (0);
}
