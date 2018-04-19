/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vcpu_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 17:46:19 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vcpu_types.h"
#include "corewar_types.h"
#include "vcpu.h"
#include "vcpu_verbose.h"

int		live_instr(t_vcpu *cpu, t_process *p, t_player *pl, t_gamectrl *g)
{
	uint32_t	nbl;
	uint8_t		alive;
	t_player	*p_buff;

	secure_fetch(p->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_DIRSZ);
	alive = (REG_MAXVALUE - cpu->op_args[0] + 1) & 0xFF;
	// log_this("ins", 0, P_ARG_DIR, 1, alive);
	if (alive > 0 && --alive < MAX_PLAYERS)
	{
		p_buff = pl - pl->player_no + 1;
		g->winner = alive + 1;
		g->nb_lives++;
		p->last_live = cpu->tick;
		p_buff[alive].last_live = p->last_live;
		nbl = ++p_buff[alive].nb_lives;
		if (g->alpha == 0 || nbl > p_buff[g->alpha - 1].nb_lives)
			g->alpha = alive + 1;
		else if (g->alpha - 1 != alive && nbl == p_buff[g->alpha - 1].nb_lives)
			g->alpha = 0;
		log_this("ins", 0, LIVE_OK, IDARGS, alive);
	}
	else
		log_this("ins", 0, LIVE_KO,  IDARGS, alive);
	return (ARG_DIRSZ);
}

int		ld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		r_dst;

	p->carry = 0;
	if ((r_dst = cpu->op_args[1]) != 0 && --r_dst < REG_NUMBER)
	{
		data = cpu->op_args[0];
		r = p->registers;
		if (((cpu->op_bytecode >> 6) & 3) == ARG_IND)
		{
			secure_fetch(data, cpu->memory, r + r_dst, REG_SIZE);
			log_this("ins", 0, LD_IND, IDARGS, data, r[r_dst], r_dst + 1);
		}
		else
		{
			r[r_dst] = data;
			log_this("ins", 0, LD_DIR, IDARGS, data, r_dst + 1);
		}
		p->carry = (r[r_dst] == 0);
	}
	else
		log_this("ins", 0, LD_KO, IDARGS, cpu->op_args[1]);
	return (0);
}

int		st_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		r_src;

	if ((r_src = cpu->op_args[0]) != 0 || --r_src < REG_NUMBER)
	{
		r = p->registers;
		data = cpu->op_args[1];
		if (((cpu->op_bytecode >> 4) & 3) == ARG_IND)
		{
			secure_store(data, cpu->memory, r[r_src], REG_SIZE);
			log_this("ins", 0, ST_IND, IDARGS, r_src + 1, r[r_src], data);
		}
		else if (data != 0 && --data < REG_NUMBER)
		{
			r[data] = r[r_src];
			log_this("ins", 0, ST_REG, r_src + 1, r[r_src], data + 1);
		}
		else
			log_this("ins", 0, ST_KO, IDARGS, cpu->op_args[1]);
	}
	else
		log_this("ins", 0, ST_KO, IDARGS, cpu->op_args[0]);
	return (0);
}

int		add_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		r_a;
	uint8_t		r_b;
	uint8_t		r_dst;

	p->carry = 0;
	if ((r_dst = cpu->op_args[2]) != 0 && --r_dst < REG_NUMBER
		&& (r_a = cpu->op_args[0]) != 0 && --r_a < REG_NUMBER
		&& (r_b = cpu->op_args[1]) != 0 && --r_b < REG_NUMBER)
	{
		r = p->registers;
		r[r_dst] = (uint32_t)((int)(r[r_a]) + (int)(r[r_b]));
		p->carry = (r[r_dst] == 0);
		log_this("ins", 0, ADD_OK, IDARGS, ++r_a, ++r_b, r[r_dst], r_dst + 1);
	}
	else
		log_this("ins", 0, ADD_KO, p->player_no, p->pid);
	return (0);
}

int		sub_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		r_a;
	uint8_t		r_b;
	uint8_t		r_dst;

	p->carry = 0;
	if ((r_dst = cpu->op_args[2]) != 0 && --r_dst < REG_NUMBER
		&& (r_a = cpu->op_args[0]) != 0 && --r_a < REG_NUMBER
		&& (r_b = cpu->op_args[1]) != 0 && --r_b < REG_NUMBER)
	{
		r = p->registers;
		r[r_dst] = (uint32_t)((int)(r[r_a]) - (int)(r[r_b]));
		p->carry = (r[r_dst] == 0);
		log_this("ins", 0, SUB_OK, IDARGS, ++r_a, ++r_b, r[r_dst], r_dst + 1);
	}
	else
		log_this("ins", 0, SUB_KO,  p->player_no, p->pid);
	return (0);
}

int		and_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		r_dst;

	p->carry = 0;
	arg = cpu->op_args;
	if ((r_dst = arg[2]) != 0 && --r_dst < REG_NUMBER)
	{
		r = p->registers;
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 3, arg) == FAILURE)
			return (log_this("ins", 0, AND_KO, IDARGS, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 3, arg + 1) == FAILURE)
			return (log_this("ins", 0, AND_KO, IDARGS, arg[1]));
		r[r_dst] = arg[0] & arg[1];
		p->carry = (r[r_dst] == 0);
		log_this("ins", 0, AND_OK, IDARGS, arg[0], arg[1], r[r_dst], r_dst + 1);
	}
	else
		log_this("ins", 0, AND_KO, IDARGS, arg[2]);
	return (0);
}

int		or_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		r_dst;

	p->carry = 0;
	arg = cpu->op_args;
	if ((r_dst = arg[2]) != 0 && --r_dst < REG_NUMBER)
	{
		r = p->registers;
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 3, arg) == FAILURE)
			return (log_this("ins", 0, OR_KO, IDARGS, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 3, arg + 1) == FAILURE)
			return (log_this("ins", 0, OR_KO, IDARGS, arg[1]));
		r[r_dst] = arg[0] | arg[1];
		p->carry = (r[r_dst] == 0);
		log_this("ins", 0, OR_OK, IDARGS, arg[0], arg[1], r[r_dst], r_dst + 1);
	}
	else
		log_this("ins", 0, OR_KO, IDARGS, arg[2]);
	return (0);
}

int		xor_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	*r;
	uint8_t		r_dst;

	p->carry = 0;
	arg = cpu->op_args;
	if ((r_dst = arg[2]) != 0 && --r_dst < REG_NUMBER)
	{
		r = p->registers;
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 3, arg) == FAILURE)
			return (log_this("ins", 0, XOR_KO, IDARGS, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 3, arg + 1) == FAILURE)
			return (log_this("ins", 0, XOR_KO, IDARGS, arg[1]));
		r[r_dst] = arg[0] ^ arg[1];
		p->carry = (r[r_dst] == 0);
		log_this("ins", 0, XOR_OK, IDARGS, arg[0], arg[1], r[r_dst], r_dst + 1);
	}
	else
		log_this("ins", 0, XOR_KO, IDARGS, arg[2]);
	return (0);
}

// int		zjmp_instr(t_vcpu *cpu, t_process *p)
// {
// 	int16_t	dst;
//
// 	if (p->carry == 1)
// 	{
// 		secure_fetch(p->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_INDSZ);
// 		dst = (uint16_t)((int16_t)(cpu->op_args[0] & 0xFFFF)) & (IDX_MOD - 1);
// 		// log_this("ins", 0, P_ARG_IND, 1, (int16_t)(cpu->op_args[0] & 0xFFFF));
// 		// log_this("ins", 0, P_IND_MOD, dst);
// 		log_this("ins", 0, ZJMP_OK, IDARGS, dst, p->pc + dst);
// 		p->pc = jump_to(p->pc, dst);
// 		return (-OPBC_SIZE);
// 	}
// 	else
// 	{
// 		log_this("ins", 0, ZJMP_KO, IDARGS, p->player_no, p->pid);
// 		return (ARG_INDSZ);
// 	}
// }

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
		log_this("ins", 0, ZJMP_OK, cpu->tick, p->player_no, p->pid, restricted, p->pc);
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
	int16_t		src;
	uint8_t		r_dst;

	arg = cpu->op_args;
	p->carry = 0;
	if ((r_dst = arg[2]) != 0 && --r_dst < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 3, arg) == FAILURE)
			return (log_this("ins", 0, LDI_KO, IDARGS, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 3, arg + 1) == FAILURE)
			return (log_this("ins", 0, LDI_KO, IDARGS, arg[1]));
		src = (uint16_t)((int16_t)(arg[0] & 0xFFFF)
						+ (int16_t)(arg[1] & 0xFFFF)) & (IDX_MOD - 1);
		src = jump_to(p->pc, src);
		secure_fetch(src, cpu->memory, p->registers + r_dst, REG_SIZE);
		p->carry = (p->registers[r_dst] == 0);
		log_this("ins", 0, LDI_OK, IDARGS, arg[0], arg[1],
						src, r_dst + 1, p->registers[r_dst]);
	}
	else
		log_this("ins", 0, LDI_KO, arg[2]);
	return (0);
}

int		sti_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	int16_t		dst;
	uint8_t		r_src;

	arg = cpu->op_args;
	if ((r_src = arg[0]) != 0 && --r_src < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 3, arg + 1) == FAILURE)
			return (log_this("ins", 0, LDI_KO, IDARGS, arg[1]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 2) & 3, arg + 2) == FAILURE)
			return (log_this("ins", 0, LDI_KO, IDARGS, arg[2]));
		dst = (uint16_t)((int16_t)(arg[1] & 0xFFFF)
						+ (int16_t)(arg[2] & 0xFFFF)) & (IDX_MOD - 1);
		dst = jump_to(p->pc, dst);
		secure_store(dst, cpu->memory, p->registers[r_src], REG_SIZE);
		log_this("ins", 0, STI_OK, IDARGS, r_src + 1, arg[1],
					arg[2], dst, p->registers[r_src]);
	}
	else
		log_this("ins", 0, STI_KO, arg[0]);
	return (0);
}

int		fork_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	t_process	child;
	int16_t		dst;

	++pl->nb_processes;
	++cpu->jobs->nb_processes;
	++cpu->jobs->next_pid;
	secure_fetch(p->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_INDSZ);
	dst = (uint16_t)((int16_t)(cpu->op_args[0] & 0xFFFF)) & (IDX_MOD - 1);
	child.pc = jump_to(p->pc, dst);
	child.player_no = p->player_no;
	child.carry = p->carry;
	child.timer = 0;
	child.pid = cpu->jobs->next_pid;
	child.last_live = cpu->tick;
	child.next_op = NULL;
	ft_memcpy(child.registers, p->registers, REG_LEN);
	ft_lstadd(&cpu->jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	cpu->ctrl->sleep_time = 1000000 /
		(cpu->ctrl->cycles_sec * cpu->jobs->nb_processes);
	log_this("ins", 0, FORK_OK, IDARGS, child.pid, (int32_t)cpu->op_args[0],
				child.pc);
	return (ARG_INDSZ);
}

int		lld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		r_dst;

	p->carry = 0;
	if ((r_dst = cpu->op_args[1]) != 0 && --r_dst < REG_NUMBER)
	{
		data = cpu->op_args[0];
		r = p->registers;
		if (((cpu->op_bytecode >> 6) & 3) == ARG_IND)
		{
			secure_fetch(data, cpu->memory, r + r_dst, REG_SIZE);
			log_this("ins", 0, LLD_IND, IDARGS, data, r_dst + 1, r[r_dst]);
			ft_printf("%d\n", r_dst);
		}
		else
		{
			r[r_dst] = data;
			log_this("ins", 0, LLD_DIR, IDARGS, data, r_dst + 1);
		}
		p->carry = (r[r_dst] == 0);
	}
	else
		log_this("ins", 0, LLD_KO, IDARGS, cpu->op_args[1]);
	return (0);
}

int		lldi_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*arg;
	uint32_t	data;
	uint8_t		r_dst;

	arg = cpu->op_args;
	p->carry = 0;
	if ((r_dst = arg[2]) != 0 && --r_dst < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 6) & 3, arg) == FAILURE)
			return (log_this("ins", 0, LLDI_KO, IDARGS, arg[0]));
		if (decode_arg(cpu, p, (cpu->op_bytecode >> 4) & 3, arg + 1) == FAILURE)
			return (log_this("ins", 0, LLDI_KO, IDARGS, arg[1]));
		data = arg[0] + arg[1];
		data = jump_to(p->pc, data);
		secure_fetch(data, cpu->memory, p->registers + r_dst, REG_SIZE);
		p->carry = (p->registers[r_dst] == 0);
		log_this("ins", 0, LLDI_OK, IDARGS, arg[0], arg[1],
						data, r_dst + 1, p->registers[r_dst]);
	}
	else
		log_this("ins", 0, LLDI_KO, IDARGS, arg[2]);
	return (0);
}

int		lfork_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	t_process	child;

	++pl->nb_processes;
	++cpu->jobs->nb_processes;
	++cpu->jobs->next_pid;
	secure_fetch(p->pc + OPBC_SIZE, cpu->memory, cpu->op_args, ARG_INDSZ);
	child.pc = jump_to(p->pc, cpu->op_args[0]);
	child.player_no = p->player_no;
	child.carry = p->carry;
	child.timer = 0;
	child.pid = cpu->jobs->next_pid;
	child.last_live = cpu->tick;
	child.next_op = NULL;
	ft_memcpy(child.registers, p->registers, REG_LEN);
	ft_lstadd(&cpu->jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	cpu->ctrl->sleep_time = 1000000 /
		(cpu->ctrl->cycles_sec * cpu->jobs->nb_processes);
	log_this("ins", 0, LFORK_OK, IDARGS, child.pid, (int32_t)cpu->op_args[0],
				child.pc);
	return (ARG_INDSZ);
}

int		aff_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	uint8_t		r_src;
	char		to_print;

	if ((r_src = cpu->op_args[0]) != 0 && --r_src < REG_NUMBER)
	{
		to_print = p->registers[r_src] & 0xFF;
		if (pl->aff_bytes == 0xFF || (to_print == '\0' && pl->aff_bytes > 0))
		{
			write(1, pl->aff_buff, pl->aff_bytes);
			ft_bzero(pl->aff_buff, pl->aff_bytes);
			pl->aff_bytes = 0;
		}
		else
		{
			pl->aff_buff[pl->aff_bytes] = to_print;
			++pl->aff_bytes;
		}
		log_this("ins", 0, AFF_OK, IDARGS, to_print, r_src + 1);
	}
	else
		log_this("ins", 0, AFF_KO, IDARGS, cpu->op_args[0]);
	return (0);
}
