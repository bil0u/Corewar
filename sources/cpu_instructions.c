/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 16:12:26 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "cpu.h"
#include "cpu_verbose.h"

int		live_instr(t_vcpu *cpu, t_process *p, t_player *pl, t_gamectrl *game)
{
	uint32_t	player_no;

	secure_fetch(p->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_DIRSZ);
	player_no = REG_MAXVALUE - cpu->op_args[0] + 1;
	// log_this("ins", 0, P_ARG_DIR, 1, player_no);
	if (player_no > 0 && player_no < MAX_PLAYERS + 1)
	{
		++pl->nb_lives;
		++game->nb_lives;
		p->last_live = cpu->tick;
		game->winner = player_no & 0xFF;
		log_this("ins", 0, LIVE_OK, p->player_no, p->pid, cpu->tick, player_no);
	}
	else
		log_this("ins", 0, LIVE_KO, p->player_no, p->pid, cpu->tick, player_no);
	return (ARG_DIRSZ);
}

int		ld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		reg_dst;

	p->carry = 0;
	if ((reg_dst = cpu->op_args[1]) != 0 && --reg_dst < REG_NUMBER)
	{
		data = cpu->op_args[0];
		r = p->registers;
		if (((cpu->op_bytecode >> 6) & 0x03) == ARG_IND)
		{
			secure_fetch(data, cpu->memory, r + reg_dst, REG_SIZE);
			log_this("ins", 0, LD_IND, p->player_no, p->pid, cpu->tick, data, r[reg_dst], reg_dst + 1);
		}
		else
		{
			r[reg_dst] = data;
			log_this("ins", 0, LD_DIR, p->player_no, p->pid, cpu->tick, data, reg_dst + 1);
		}
		p->carry = (r[reg_dst] == 0);
	}
	else
		log_this("ins", 0, LD_KO, p->player_no, p->pid, cpu->tick, cpu->op_args[1]);
	return (0);
}

int		st_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		reg_src;

	if ((reg_src = cpu->op_args[0]) != 0 || --reg_src < REG_NUMBER)
	{
		r = p->registers;
		data = cpu->op_args[1];
		if (((cpu->op_bytecode >> 4) & 0x03) == ARG_IND)
		{
			secure_store(data, cpu->memory, r[reg_src], REG_SIZE);
			log_this("ins", 0, ST_IND, p->player_no, p->pid, cpu->tick, reg_src + 1, r[reg_src], data);
		}
		else if (data != 0 && --data < REG_NUMBER)
		{
			r[data] = r[reg_src];
			log_this("ins", 0, ST_REG, reg_src + 1, r[reg_src], data + 1);
		}
		else
			log_this("ins", 0, ST_KO, p->player_no, p->pid, cpu->tick, cpu->op_args[1]);
	}
	else
		log_this("ins", 0, ST_KO, p->player_no, p->pid, cpu->tick, cpu->op_args[0]);
	return (0);
}

int		add_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	p->carry = 0;
	if ((reg_dst = cpu->op_args[2]) != 0 && --reg_dst < REG_NUMBER
		&& (reg_a = cpu->op_args[0]) != 0 && --reg_a < REG_NUMBER
		&& (reg_b = cpu->op_args[1]) != 0 && --reg_b < REG_NUMBER)
	{
		r = p->registers;
		r[reg_dst] = (uint32_t)((int)(r[reg_a]) + (int)(r[reg_b]));
		p->carry = (r[reg_dst] == 0);
		log_this("ins", 0, ADD_OK, p->player_no, p->pid, cpu->tick, ++reg_a, ++reg_b, r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, ADD_KO, p->player_no, p->pid);
	return (0);
}

int		sub_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		reg_a;
	uint8_t		reg_b;
	uint8_t		reg_dst;

	p->carry = 0;
	if ((reg_dst = cpu->op_args[2]) != 0 && --reg_dst < REG_NUMBER
		&& (reg_a = cpu->op_args[0]) != 0 && --reg_a < REG_NUMBER
		&& (reg_b = cpu->op_args[1]) != 0 && --reg_b < REG_NUMBER)
	{
		r = p->registers;
		r[reg_dst] = (uint32_t)((int)(r[reg_a]) - (int)(r[reg_b]));
		p->carry = (r[reg_dst] == 0);
		log_this("ins", 0, SUB_OK, p->player_no, p->pid, cpu->tick, ++reg_a, ++reg_b, r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, SUB_KO,  p->player_no, p->pid);
	return (0);
}

int		and_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		reg_dst;

	p->carry = 0;
	arg = cpu->op_args;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		r = p->registers;
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, AND_KO, p->player_no, p->pid, cpu->tick, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, AND_KO, p->player_no, p->pid, cpu->tick, arg[1]));
		r[reg_dst] = arg[0] & arg[1];
		p->carry = (r[reg_dst] == 0);
		log_this("ins", 0, AND_OK, p->player_no, p->pid, cpu->tick, arg[0], arg[1], r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, AND_KO, p->player_no, p->pid, cpu->tick, arg[2]);
	return (0);
}

int		or_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		reg_dst;

	p->carry = 0;
	arg = cpu->op_args;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		r = p->registers;
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, OR_KO, p->player_no, p->pid, cpu->tick, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, OR_KO, p->player_no, p->pid, cpu->tick, arg[1]));
		r[reg_dst] = arg[0] | arg[1];
		p->carry = (r[reg_dst] == 0);
		log_this("ins", 0, OR_OK, p->player_no, p->pid, cpu->tick, arg[0], arg[1], r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, OR_KO, p->player_no, p->pid, cpu->tick, arg[2]);
	return (0);
}

int		xor_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		reg_dst;

	p->carry = 0;
	arg = cpu->op_args;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		r = p->registers;
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, XOR_KO, p->player_no, p->pid, cpu->tick, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, XOR_KO, p->player_no, p->pid, cpu->tick, arg[1]));
		r[reg_dst] = arg[0] ^ arg[1];
		p->carry = (r[reg_dst] == 0);
		log_this("ins", 0, XOR_OK, p->player_no, p->pid, cpu->tick, arg[0], arg[1], r[reg_dst], reg_dst + 1);
	}
	else
		log_this("ins", 0, XOR_KO, p->player_no, p->pid, cpu->tick, arg[2]);
	return (0);
}

int		zjmp_instr(t_vcpu *cpu, t_process *p)
{
	int16_t		restricted;

	if (p->carry == 1)
	{
		secure_fetch(p->pc + OPBC_SIZE, cpu->memory,
										cpu->op_args, ARG_INDSZ);
		restricted = (int16_t)(cpu->op_args[0] & 0xFFFF) % IDX_MOD;
		p->pc = jump_to(p->pc, restricted);
		// log_this("ins", 0, P_ARG_IND, 1, (int16_t)(cpu->op_args[0] & 0xFFFF));
		// log_this("ins", 0, P_IND_MOD, restricted);
		log_this("ins", 0, ZJMP_OK, p->player_no, p->pid, cpu->tick, restricted, p->pc);
		return (-OPBC_SIZE);
	}
	else
	{
		log_this("ins", 0, ZJMP_KO, p->player_no, p->pid);
		return (ARG_INDSZ);
	}
}

int		ldi_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	data;
	uint8_t		reg_dst;

	arg = cpu->op_args;
	p->carry = 0;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, LDI_KO, p->player_no, p->pid, cpu->tick, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, LDI_KO, p->player_no, p->pid, cpu->tick, arg[1]));
		data = ((int)arg[0] + (int)arg[1]) % IDX_MOD;
		data = jump_to(p->pc, (int)data);
		secure_fetch(data, cpu->memory, p->registers + reg_dst, REG_SIZE);
		p->carry = (p->registers[reg_dst] == 0);
		log_this("ins", 0, LDI_OK, p->player_no, p->pid, cpu->tick, arg[0], arg[1],
						data, reg_dst + 1, p->registers[reg_dst]);
	}
	else
		log_this("ins", 0, LDI_KO, arg[2]);
	return (0);
}

int		sti_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	data;
	uint8_t		reg_src;

	arg = cpu->op_args;
	if ((reg_src = arg[0]) != 0 && --reg_src < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, LDI_KO, p->player_no, p->pid, cpu->tick, arg[1]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 2) & 0x03, arg + 2) == FAILURE)
			return (log_this("ins", 0, LDI_KO, p->player_no, p->pid, cpu->tick, arg[2]));
		data = ((int)arg[1] + (int)arg[2]) % IDX_MOD;
		data = jump_to(p->pc, (int)data);
		secure_store(data, cpu->memory, p->registers[reg_src], REG_SIZE);
		log_this("ins", 0, STI_OK, p->player_no, p->pid, cpu->tick, reg_src + 1, arg[1],
					arg[2], data, p->registers[reg_src]);
	}
	else
		log_this("ins", 0, STI_KO, arg[0]);
	return (0);
}

int		fork_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	t_process	child;

	++pl->nb_processes;
	++cpu->jobs->nb_processes;
	++cpu->jobs->next_pid;
	secure_fetch(p->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_INDSZ);
	cpu->op_args[0] = (uint32_t)(((int32_t)cpu->op_args[0]) % IDX_MOD);
	child.pc = jump_to(p->pc, (int32_t)cpu->op_args[0]);
	child.player_no = p->player_no;
	child.carry = p->carry;
	child.timer = 0;
	child.pid = cpu->jobs->next_pid;
	child.last_live = cpu->tick;
	child.next_op = NULL;
	ft_memcpy(child.registers, p->registers, REG_LEN);
	ft_lstadd(&cpu->jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	if (cpu->ctrl->flags & CWF_SLOW)
		cpu->ctrl->sleep_time = 1000000 /
			(cpu->ctrl->cycles_sec * cpu->jobs->nb_processes);
	log_this("ins", 0, FORK_OK, p->player_no, p->pid, cpu->tick, child.pid, p->pc,
								(int32_t)cpu->op_args[0], child.pc);
	return (ARG_INDSZ);
}

int		lld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		reg_dst;

	p->carry = 0;
	if ((reg_dst = cpu->op_args[1]) != 0 && --reg_dst < REG_NUMBER)
	{
		data = cpu->op_args[0];
		r = p->registers;
		if (((cpu->op_bytecode >> 6) & 0x03) == ARG_IND)
		{
			secure_fetch(data, cpu->memory, r + reg_dst, REG_SIZE);
			log_this("ins", 0, LLD_IND, p->player_no, p->pid, cpu->tick, data, reg_dst + 1, r[reg_dst]);
			ft_printf("%d\n", reg_dst);
		}
		else
		{
			r[reg_dst] = data;
			log_this("ins", 0, LLD_DIR, p->player_no, p->pid, cpu->tick, data, reg_dst + 1);
		}
		p->carry = (r[reg_dst] == 0);
	}
	else
		log_this("ins", 0, LLD_KO, p->player_no, p->pid, cpu->tick, cpu->op_args[1]);
	return (0);
}

int		lldi_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	data;
	uint8_t		reg_dst;

	arg = cpu->op_args;
	p->carry = 0;
	if ((reg_dst = arg[2]) != 0 && --reg_dst < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 0x03, arg) == FAILURE)
			return (log_this("ins", 0, LLDI_KO, p->player_no, p->pid, cpu->tick, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 0x03, arg + 1) == FAILURE)
			return (log_this("ins", 0, LLDI_KO, p->player_no, p->pid, cpu->tick, arg[1]));
		data = ((int)arg[0] + (int)arg[1]);
		data = jump_to(p->pc, (int)data);
		secure_fetch(data, cpu->memory, p->registers + reg_dst, REG_SIZE);
		p->carry = (p->registers[reg_dst] == 0);
		log_this("ins", 0, LLDI_OK, p->player_no, p->pid, cpu->tick, arg[0], arg[1],
						data, reg_dst + 1, p->registers[reg_dst]);
	}
	else
		log_this("ins", 0, LLDI_KO, p->player_no, p->pid, cpu->tick, arg[2]);
	return (0);
}

int		lfork_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	t_process	child;

	++pl->nb_processes;
	++cpu->jobs->nb_processes;
	++cpu->jobs->next_pid;
	secure_fetch(p->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_INDSZ);
	child.pc = jump_to(p->pc, (int32_t)cpu->op_args[0]);
	child.player_no = p->player_no;
	child.carry = p->carry;
	child.timer = 0;
	child.pid = cpu->jobs->next_pid;
	child.last_live = cpu->tick;
	child.next_op = NULL;
	ft_memcpy(child.registers, p->registers, REG_LEN);
	ft_lstadd(&cpu->jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	if (cpu->ctrl->flags & CWF_SLOW)
		cpu->ctrl->sleep_time = 1000000 /
			(cpu->ctrl->cycles_sec * cpu->jobs->nb_processes);
	log_this("ins", 0, LFORK_OK, p->player_no, p->pid, cpu->tick, child.pid, p->pc,
								(int32_t)cpu->op_args[0], child.pc);
	return (ARG_INDSZ);
}

int		aff_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	uint8_t		reg_src;
	char		to_print;

	if ((reg_src = cpu->op_args[0]) != 0 && --reg_src < REG_NUMBER)
	{
		to_print = p->registers[reg_src] & 0xFF;
		if (to_print == '\0' && pl->aff_bytes > 0)
			write(1, pl->aff_buff, pl->aff_bytes);
		else if (to_print != '\0')
		{
			pl->aff_buff[pl->aff_bytes] = to_print;
			++to_print;
		}
		log_this("ins", 0, AFF_OK, p->player_no, p->pid, cpu->tick, to_print, reg_src + 1);
	}
	else
		log_this("ins", 0, AFF_KO, p->player_no, p->pid, cpu->tick, cpu->op_args[0]);
	return (0);
}
