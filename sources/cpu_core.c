/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/03/05 05:37:19 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "instructions.h"
#include "cpu.h"

static uint8_t	fetch_next_arg(uint8_t bmask, uint8_t *pc, t_arg *arg_buff)
{
	uint8_t		arg_type;
	uint8_t		bytes_read;

	arg_type = (bmask & 0xC0) >> 6;
	bytes_read = 0;
	if (arg_type == ARG_REG)
	{
		arg_buff->reg_no = *pc;
		bytes_read = sizeof(arg_buff->reg_no);
	}
	else if (arg_type == ARG_IND)
	{
		arg_buff->ind = SWAP_UINT16(*((uint16_t *)(pc)));
		bytes_read = sizeof(arg_buff->ind);
	}
	else if (arg_type == ARG_DIR)
	{
		arg_buff->dir = SWAP_UINT32(*((uint32_t *)(pc)));
		bytes_read = sizeof(arg_buff->dir);
	}
	return (bytes_read);
}


static void		fetch_arguments(t_vcpu *cpu, uint8_t *bytes_read)
{
	uint8_t		*arg_data;
	uint8_t 	bitmask;
	uint8_t		arg_no;
	uint8_t		arg_sz;

	bitmask = *((uint8_t *)(cpu->vm_memory + JUMP_OF(cpu->pc, *bytes_read)));
	ft_printf("{blue}Read bitmask %#8.8b{eoc}\n", bitmask);
	*bytes_read += 1;
	arg_no = 0;
	while (arg_no < cpu->curr_instruction->nb_args)
	{
		arg_data = cpu->vm_memory + JUMP_OF(cpu->pc, *bytes_read);
		arg_sz = fetch_next_arg(bitmask, arg_data, cpu->args_buff + arg_no);
		ft_printf("{blue}Fetched arg #%d [%d byte(s)]{eoc}\n", arg_no + 1, arg_sz);
		*bytes_read += arg_sz;
		bitmask <<= 2;
		++arg_no;
	}
}

static void		fetch_instruction(t_vcpu *cpu)
{
	uint8_t		op_no;
	uint8_t		bytes_read;

	op_no = cpu->vm_memory[cpu->pc];
	cpu->curr_instruction = &(g_op_set[op_no]);
	bytes_read = 1;
	if (op_no != 0)
	{
		ft_printf("{yellow}## Fetched instruction %#2.2x{eoc}\n", op_no);
		cpu->curr_instruction = &(g_op_set[op_no]);
		if (cpu->curr_instruction->nb_args > 0)
		{
			ft_printf("{blue} > Fetching args ...{eoc}\n");
			fetch_arguments(cpu, &bytes_read);
		}
	}
	cpu->pc = (cpu->pc + bytes_read) % MEM_SIZE;

	if (cpu->curr_instruction->nb_args > 0)
		ft_printf("{yellow}#### > %d args on %d byte(s){eoc}\n", cpu->curr_instruction->nb_args, bytes_read - 2);
}

void			run_cpu(t_vcpu *cpu, uint64_t nb_cycles)
{
	uint64_t	cycle_no;

	cycle_no = 1;
	while (cycle_no <= nb_cycles)
	{
		print_memory("Memory   ", cpu->vm_memory, MEM_SIZE, cpu->pc);
		//print_memory("Registers", registers, REG_LEN, NULL);
		fetch_instruction(cpu);
		if (cpu->curr_instruction->op_number != 0)
		{
			ft_printf("{blue}Executing instruction #%d '%s'{eoc}\n", cpu->curr_instruction->op_number,
																	cpu->curr_instruction->name);
			cpu->curr_instruction->funct_ptr(cpu->vm_memory, cpu->registers,
											&cpu->carry, cpu->args_buff);
		}
		++cycle_no;
	}
}


int				main(void)
{
	uint8_t		ram[MEM_SIZE];
	uint8_t		registers[REG_LEN];
	t_vcpu		cpu;

	ft_bzero(&ram, MEM_SIZE);
	ft_bzero(&registers, REG_LEN);

	ram[0] = 0x01;
	ram[1] = 0x80;
	ram[2] = 0x00;
	ram[3] = 0x00;
	ram[4] = 0x00;
	ram[5] = 0x01;

	init_cpu(&cpu, ram);
	load_process(&cpu, registers, 0);

	run_cpu(&cpu, 100);

	return (0);
}
