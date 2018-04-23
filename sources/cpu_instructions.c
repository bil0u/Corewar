/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 03:09:09 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

int		live_instr(t_vcpu *cpu, t_process *p, t_player *pl, t_gamectrl *g)
{
	uint32_t	nbl;
	uint8_t		alive;
	t_player	*p_buff;

	secure_fetch(p->pc + OPBC_SIZE, CPU_MEM, CPU_ARG, ARG_DIRSZ);
	alive = (REG_MAXVALUE - (int)CPU_ARG[0] + 1) & 0xFF;
	if (alive > 0 && alive < MAX_PLAYERS + 1)
	{
		p_buff = pl - pl->player_no + 1;
		g->winner = alive--;
		g->nb_lives++;
		p->last_live = cpu->tick;
		p_buff[alive].last_live = p->last_live;
		nbl = ++p_buff[alive].nb_lives;
		if (g->alpha == 0 || nbl > p_buff[g->alpha - 1].nb_lives)
			g->alpha = alive + 1;
		else if (g->alpha - 1 != alive && nbl == p_buff[g->alpha - 1].nb_lives)
			g->alpha = 0;
		INS_DEB ? log_this(IDW, LIVE_OK, IDA, alive + 1) : 0;
	}
	else
		INS_DEB ? log_this(IDW, LIVE_KO, IDA, alive - 1) : 0;
	INS_VERB ? ft_printf(V_LIVE, IVA, CPU_ARG[0]) : 0;
	return (ARG_DIRSZ);
}

int		ld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[1]) != 0 && --dst < REG_NUMBER && (r = p->registers))
	{
		data = CPU_ARG[0];
		if (((CPU_OPBC >> 6) & 3) == ARG_IND)
		{
			secure_fetch(jump_to(p->pc, (int)(CPU_ARG[0] & 0xFFFF)), CPU_MEM, r + dst, REG_SIZE);
			INS_DEB ? log_this(IDW, LD_IND, IDA, data, r[dst], dst + 1) : 0;
			INS_VERB ? ft_printf(V_LD, IVA, r[dst], dst + 1) : 0;
		}
		else
		{
			r[dst] = data;
			INS_DEB ? log_this(IDW, LD_DIR, IDA, data, dst + 1) : 0;
			INS_VERB ? ft_printf(V_LD, IVA, data, dst + 1) : 0;
		}
		p->carry = (r[dst] == 0);
	}
	else
		INS_DEB ? log_this(IDW, LD_KO, IDA, CPU_ARG[1]) : 0;
	return (0);
}

int		st_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		src;

	if ((src = CPU_ARG[0]) != 0 && --src < REG_NUMBER && (r = p->registers))
	{
		data = CPU_ARG[1];
		if (((CPU_OPBC >> 4) & 3) == ARG_IND)
		{
			secure_store(data, CPU_MEM, r[src], REG_SIZE);
			INS_DEB ? log_this(IDW, ST_IND, IDA, src + 1, r[src], data) : 0;
		}
		else if (data != 0 && --data < REG_NUMBER)
		{
			r[data] = r[src];
			INS_DEB ? log_this(IDW, ST_REG, IDA, src + 1, r[src], data + 1) : 0;
		}
		else
			return (INS_DEB ? log_this(IDW, ST_KO, IDA, CPU_ARG[1]) : 0);
		INS_VERB ? ft_printf(V_ST, IVA, src + 1, r[src]) : 0;
	}
	else
		INS_DEB ? log_this(IDW, ST_KO, IDA, CPU_ARG[0]) : 0;
	return (0);
}

int		add_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		r_a;
	uint8_t		r_b;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[2]) != 0 && --dst < REG_NUMBER
		&& (r_a = CPU_ARG[0]) != 0 && --r_a < REG_NUMBER
		&& (r_b = CPU_ARG[1]) != 0 && --r_b < REG_NUMBER && (r = p->registers))
	{
		r[dst] = (uint32_t)((int)(r[r_a]) + (int)(r[r_b]));
		p->carry = (r[dst] == 0);
		INS_DEB ? log_this(IDW, ADD_OK, IDA,
			r_a + 1, r_b + 1, r[dst], dst + 1) : 0;
		INS_VERB ? ft_printf(V_ADD, IVA, r_a + 1, r_b + 1, dst + 1) : 0;
	}
	else
		INS_DEB ? log_this(IDW, ADD_KO, IDA, p->player_no, p->pid) : 0;
	return (0);
}

int		sub_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		r_a;
	uint8_t		r_b;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[2]) != 0 && --dst < REG_NUMBER
		&& (r_a = CPU_ARG[0]) != 0 && --r_a < REG_NUMBER
		&& (r_b = CPU_ARG[1]) != 0 && --r_b < REG_NUMBER && (r = p->registers))
	{
		r[dst] = (uint32_t)((int)(r[r_a]) - (int)(r[r_b]));
		p->carry = (r[dst] == 0);
		INS_DEB ? log_this(IDW, SUB_OK, IDA,
			r_a + 1, r_b + 1, r[dst], dst + 1) : 0;
		INS_VERB ? ft_printf(V_SUB, IVA, r_a + 1, r_b + 1, dst + 1) : 0;
	}
	else
		INS_DEB ? log_this(IDW, SUB_KO, IDA, p->player_no, p->pid) : 0;
	return (0);
}

int		and_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[2]) != 0 && --dst < REG_NUMBER && (r = p->registers))
	{
		if (decode_arg(cpu, p, (CPU_OPBC >> 6) & 3, CPU_ARG) == FAILURE)
			return (INS_DEB ? log_this(IDW, AND_KO, IDA, CPU_ARG[0]) : 0);
		if (decode_arg(cpu, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1) == FAILURE)
			return (INS_DEB ? log_this(IDW, AND_KO, IDA, CPU_ARG[1]) : 0);
		r[dst] = CPU_ARG[0] & CPU_ARG[1];
		p->carry = (r[dst] == 0);
		INS_DEB ? log_this(IDW, AND_OK, IDA,
			CPU_ARG[0], CPU_ARG[1], r[dst], dst + 1) : 0;
		INS_VERB ? ft_printf(V_AND, IVA, CPU_ARG[0], CPU_ARG[1], dst + 1) : 0;
	}
	else
		INS_DEB ? log_this(IDW, AND_KO, IDA, CPU_ARG[2]) : 0;
	return (0);
}

int		or_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[2]) != 0 && --dst < REG_NUMBER && (r = p->registers))
	{
		if (decode_arg(cpu, p, (CPU_OPBC >> 6) & 3, CPU_ARG) == FAILURE)
			return (INS_DEB ? log_this(IDW, OR_KO, IDA, CPU_ARG[0]) : 0);
		if (decode_arg(cpu, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1) == FAILURE)
			return (INS_DEB ? log_this(IDW, OR_KO, IDA, CPU_ARG[1]) : 0);
		r[dst] = CPU_ARG[0] | CPU_ARG[1];
		p->carry = (r[dst] == 0);
		INS_DEB ? log_this(IDW, OR_OK, IDA,
			CPU_ARG[0], CPU_ARG[1], r[dst], dst + 1) : 0;
		INS_VERB ? ft_printf(V_OR, IVA, CPU_ARG[0], CPU_ARG[1], dst + 1) : 0;
	}
	else
		INS_DEB ? log_this(IDW, OR_KO, IDA, CPU_ARG[2]) : 0;
	return (0);
}

int		xor_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[2]) != 0 && --dst < REG_NUMBER && (r = p->registers))
	{
		if (decode_arg(cpu, p, (CPU_OPBC >> 6) & 3, CPU_ARG) == FAILURE)
			return (INS_DEB ? log_this(IDW, XOR_KO, IDA, CPU_ARG[0]) : 0);
		if (decode_arg(cpu, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1) == FAILURE)
			return (INS_DEB ? log_this(IDW, XOR_KO, IDA, CPU_ARG[1]) : 0);
		r[dst] = CPU_ARG[0] ^ CPU_ARG[1];
		p->carry = (r[dst] == 0);
		INS_DEB ? log_this(IDW, XOR_OK, IDA,
			CPU_ARG[0], CPU_ARG[1], r[dst], dst + 1) : 0;
		INS_VERB ? ft_printf(V_XOR, IVA, CPU_ARG[0], CPU_ARG[1], dst + 1) : 0;
	}
	else
		INS_DEB ? log_this(IDW, XOR_KO, IDA, CPU_ARG[2]) : 0;
	return (0);
}

int		zjmp_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	pc_dst;
	int16_t		ind;

	secure_fetch(p->pc + OPBC_SIZE, CPU_MEM, CPU_ARG, ARG_INDSZ);
	ind = (int16_t)(CPU_ARG[0] & 0xFFFF) % IDX_MOD;
	if (p->carry == 1)
	{
		pc_dst = jump_to(p->pc, (int)ind);
		INS_DEB ? log_this(IDW, ZJMP_OK, IDA, ind, pc_dst) : 0;
		INS_VERB ? ft_printf(V_ZJMPOK, IVA, ind) : 0;
		p->pc = pc_dst;
		return (-OPBC_SIZE);
	}
	else
	{
		INS_DEB ? log_this(IDW, ZJMP_KO, IDA, ind) : 0;
		INS_VERB ? ft_printf(V_ZJMPKO, IVA, ind) : 0;
		return (ARG_INDSZ);
	}
}

int		ldi_instr(t_vcpu *cpu, t_process *p)
{
	int32_t		ind;
	uint32_t	data;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[2]) != 0 && --dst < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (CPU_OPBC >> 6) & 3, CPU_ARG) == FAILURE)
			return (INS_DEB ? log_this(IDW, LDI_KO, IDA, CPU_ARG[0]) : 0);
		if (decode_arg(cpu, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1) == FAILURE)
			return (INS_DEB ? log_this(IDW, LDI_KO, IDA, CPU_ARG[1]) : 0);
		ind = (((int32_t)CPU_ARG[1] + (int32_t)CPU_ARG[2]) % IDX_MOD) & 0xFFFF;
		data = jump_to(p->pc, (int)ind);
		secure_fetch(data, CPU_MEM, p->registers + dst, REG_SIZE);
		p->carry = (p->registers[dst] == 0);
		INS_DEB ? log_this(IDW, LDI_OK, IDA, CPU_ARG[0], CPU_ARG[1],
			data, dst + 1, p->registers[dst]) : 0;
		INS_VERB ? ft_printf(V_LDI, IVA, CPU_ARG[0], CPU_ARG[1], dst + 1,
			CPU_ARG[0], CPU_ARG[1], CPU_ARG[0] + CPU_ARG[1], ind + p->pc) : 0;
	}
	else
		INS_DEB ? log_this(IDW, LDI_KO, IDA, CPU_ARG[2]) : 0;
	return (0);
}

int		sti_instr(t_vcpu *cpu, t_process *p)
{
	int32_t		ind;
	uint32_t	data;
	uint8_t		src;

	if ((src = CPU_ARG[0]) != 0 && --src < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1) == FAILURE)
			return (INS_DEB ? log_this(IDW, LDI_KO, IDA, CPU_ARG[1]) : 0);
		if (decode_arg(cpu, p, (CPU_OPBC >> 2) & 3, CPU_ARG + 2) == FAILURE)
			return (INS_DEB ? log_this(IDW, LDI_KO, IDA, CPU_ARG[2]) : 0);
		ind = (((int32_t)CPU_ARG[1] + (int32_t)CPU_ARG[2]) % IDX_MOD) & 0xFFFF;
		data = jump_to(p->pc, (int)ind);
		secure_store(data, CPU_MEM, p->registers[src], REG_SIZE);
		INS_DEB ? log_this(IDW, STI_OK, IDA, src + 1, CPU_ARG[1],
			CPU_ARG[2], data, p->registers[src]) : 0;
		INS_VERB ? ft_printf(V_STI, IVA, src + 1, CPU_ARG[0], CPU_ARG[1],
			CPU_ARG[0], CPU_ARG[1], CPU_ARG[0] + CPU_ARG[1], ind + p->pc) : 0;
	}
	else
		INS_DEB ? log_this(IDW, STI_KO, IDA, CPU_ARG[0]) : 0;
	return (0);
}

int		fork_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	t_process	child;
	int16_t		data;

	++pl->nb_processes;
	++cpu->jobs->nb_processes;
	++cpu->jobs->next_pid;
	ft_bzero(&child, sizeof(child));
	secure_fetch(p->pc + OPBC_SIZE, CPU_MEM, CPU_ARG, ARG_INDSZ);
	data = (int16_t)(CPU_ARG[0] & 0xFFF) % IDX_MOD;
	child.pc = jump_to(p->pc, (int)data);
	child.player_no = p->player_no;
	child.carry = p->carry;
	child.pid = cpu->jobs->next_pid;
	child.last_live = cpu->tick + 1;
	ft_memcpy(child.registers, p->registers, REG_LEN);
	ft_lstadd(&cpu->jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	if (cpu->ctrl->flags & CWF_SLOW)
		cpu->ctrl->sleep_time = 1000000 /
			(cpu->ctrl->cycles_sec * cpu->jobs->nb_processes);
	INS_DEB ? log_this(IDW, FORK_OK, IDA, child.pid,
		(int32_t)CPU_ARG[0], child.pc) : 0;
	INS_VERB ? ft_printf(V_FORK, IVA, data, child.pc) : 0;
	return (ARG_INDSZ);
}

int		lld_instr(t_vcpu *cpu, t_process *p)
{
	uint32_t	*r;
	uint32_t	data;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[1]) != 0 && --dst < REG_NUMBER && (r = p->registers))
	{
		data = CPU_ARG[0];
		if (((CPU_OPBC >> 6) & 3) == ARG_IND)
		{
			secure_fetch(jump_to(p->pc, (int)data), CPU_MEM, r + dst, REG_SIZE);
			INS_DEB ? log_this(IDW, LLD_IND, IDA, data, dst + 1, r[dst]) : 0;
		}
		else
		{
			r[dst] = data;
			INS_DEB ? log_this(IDW, LLD_DIR, IDA, data, dst + 1) : 0;
		}
		p->carry = (r[dst] == 0);
		INS_VERB ? ft_printf(V_LD, IVA, r[dst], dst + 1) : 0;
	}
	else
		INS_DEB ? log_this(IDW, LLD_KO, IDA, CPU_ARG[1]) : 0;
	return (0);
}

int		lldi_instr(t_vcpu *cpu, t_process *p)
{
	int32_t		ind;
	uint32_t	data;
	uint8_t		dst;

	p->carry = 0;
	if ((dst = CPU_ARG[2]) != 0 && --dst < REG_NUMBER)
	{
		if (decode_arg(cpu, p, (CPU_OPBC >> 6) & 3, CPU_ARG) == FAILURE)
			return (INS_DEB ? log_this(IDW, LLDI_KO, IDA, CPU_ARG[0]) : 0);
		if (decode_arg(cpu, p, (CPU_OPBC >> 4) & 3, CPU_ARG + 1) == FAILURE)
			return (INS_DEB ? log_this(IDW, LLDI_KO, IDA, CPU_ARG[1]) : 0);
		ind = CPU_ARG[0] + CPU_ARG[1];
		data = jump_to(p->pc, (int)ind);
		secure_fetch(data, CPU_MEM, p->registers + dst, REG_SIZE);
		p->carry = (p->registers[dst] == 0);
		INS_DEB ? log_this(IDW, LLDI_OK, IDA, CPU_ARG[0], CPU_ARG[1],
			data, dst + 1, p->registers[dst]) : 0;
		INS_VERB ? ft_printf(V_LLDI, IVA, CPU_ARG[0], CPU_ARG[1], dst + 1,
			CPU_ARG[0], CPU_ARG[1], CPU_ARG[0] + CPU_ARG[1], ind + p->pc) : 0;

	}
	else
		INS_DEB ? log_this(IDW, LLDI_KO, IDA, CPU_ARG[2]) : 0;
	return (0);
}

int		lfork_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	t_process	child;
	int16_t		data;

	++pl->nb_processes;
	++cpu->jobs->nb_processes;
	++cpu->jobs->next_pid;
	ft_bzero(&child, sizeof(child));
	secure_fetch(p->pc + OPBC_SIZE, CPU_MEM, CPU_ARG, ARG_INDSZ);
	data = (int16_t)(CPU_ARG[0] & 0xFFF);
	child.pc = jump_to(p->pc, (int)data);
	child.player_no = p->player_no;
	child.carry = p->carry;
	child.pid = cpu->jobs->next_pid;
	child.last_live = cpu->tick + 1;
	ft_memcpy(child.registers, p->registers, REG_LEN);
	ft_lstadd(&cpu->jobs->p_stack, ft_lstnew(&child, sizeof(child)));
	if (cpu->ctrl->flags & CWF_SLOW)
		cpu->ctrl->sleep_time = 1000000 /
			(cpu->ctrl->cycles_sec * cpu->jobs->nb_processes);
	INS_DEB ? log_this(IDW, FORK_OK, IDA, child.pid,
		(int32_t)CPU_ARG[0], child.pc) : 0;
	INS_VERB ? ft_printf(V_LFORK, IVA, data, child.pc) : 0;
	return (ARG_INDSZ);
}

int		aff_instr(t_vcpu *cpu, t_process *p, t_player *pl)
{
	uint8_t		src;
	char		to_print;

	if ((src = CPU_ARG[0]) != 0 && --src < REG_NUMBER)
	{
		to_print = p->registers[src] & 0xFF;
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
		INS_DEB ? log_this(IDW, AFF_OK, IDA, to_print, src + 1) : 0;
		cpu->ctrl->flags & CWF_AFFON ? ft_printf(V_AFF, to_print) : 0;
	}
	else
		INS_DEB ? log_this(IDW, AFF_KO, IDA, CPU_ARG[0]) : 0;
	return (0);
}
