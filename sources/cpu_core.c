/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 16:50:15 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "instructions.h"
#include "cpu.h"

static uint8_t	fetch_next_arg(uint8_t bmask, void *pc, t_arg *arg_buff)
{
	uint8_t		arg_type;
	uint8_t		bytes_read;

	arg_type = (bmask & 0xC0) >> 6;
	bytes_read = 0;
	if (arg_type == ARG_REG)
	{
		arg_buff->reg = pc;
		bytes_read = 1;
	}
	else if (arg_type == ARG_IND)
	{
		arg_buff->ind = *((uint16_t *)(pc));
		bytes_read = 2;
	}
	else if (arg_type == ARG_DIR)
	{
		arg_buff->dir = *((uint32_t *)(pc));
		bytes_read = 4;
	}
	return (bytes_read);
}


static void		fetch_arguments(t_vcpu *cpu, uint8_t *bytes_read)
{
	t_arg		*arg_dst;
	uint8_t 	bitmask;
	uint8_t		curr_arg;
	uint8_t		arg_size;

	bitmask = *((uint8_t *)(cpu->pc + *bytes_read));
	ft_printf("{blue}Read bitmask %#8.8b{eoc}\n", bitmask);
	*bytes_read += 1;
	curr_arg = 0;
	while (curr_arg < cpu->curr_instruction->nb_args)
	{
		arg_dst = cpu->args_buff + curr_arg;
		arg_size = fetch_next_arg(bitmask, cpu->pc + *bytes_read, arg_dst);
		ft_printf("{blue}Fetched arg #%d [%d byte(s)]{eoc}\n", curr_arg + 1, arg_size);
		*bytes_read += arg_size;
		bitmask <<= 2;
		curr_arg++;
	}
}

static void		fetch_instruction(t_vcpu *cpu)
{
	uint8_t		op_no;
	uint8_t		bytes_read;

	ft_printf("{blue}Fetching next instruction ...{eoc}\n");

	op_no = *((uint8_t *)cpu->pc);
	cpu->curr_instruction = &(g_op_set[op_no]);
	bytes_read = 1;
	if (cpu->curr_instruction->nb_args > 0)
	{
		ft_printf("{blue} > Fetching args ...{eoc}\n");
		fetch_arguments(cpu, &bytes_read);
	}
	cpu->pc += bytes_read % MEM_SIZE;

	ft_printf("{yellow}## Fetched instruction %#2.2X [%d byte(s)]{eoc}\n", op_no, bytes_read);
	if (cpu->curr_instruction->nb_args > 0)
		ft_printf("{yellow}#### > %d args on %d byte(s){eoc}\n", cpu->curr_instruction->nb_args, bytes_read - 2);
}

static void		exec_next_instruction(t_vcpu *cpu)
{
	fetch_instruction(cpu);
//	ft_printf("{blue}Executing instruction #%d '%s'{eoc}\n",
//		op_no, g_op_set[op_no].name);
//	g_op_set[op_no].funct_ptr(cpu);
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

	init_cpu(&cpu);
	load_process(&cpu, registers, ram);

	print_memory("Memory   ", ram, MEM_SIZE, cpu.pc);
	print_memory("Registers", registers, REG_LEN, NULL);
//	print_cpu(&cpu);

	exec_next_instruction(&cpu);

	print_memory("Memory   ", ram, MEM_SIZE, cpu.pc);
	print_memory("Registers", registers, REG_LEN, NULL);

	return (0);
}
