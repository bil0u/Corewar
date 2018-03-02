/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 04:02:06 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu.h"
#include "instructions.h"

#define BUFF_SIZE 32

static void		 init_cpu(t_vcpu *cpu)
{
	ft_bzero(cpu, sizeof(*cpu));
}

static void 	load_process(t_vcpu *cpu, void *process_regs, void *process_pc)
{
	cpu->registers = process_regs;
	cpu->pc = process_pc;
}

static void		exec_next_instruction(t_vcpu *cpu)
{
	uint8_t		op_no;

	op_no = *((uint8_t *)CPU_PC(cpu));
	ft_printf("{blue}Executing instruction #%d '%s'{eoc}\n",
		op_no, CPU_OP_NO(op_no).name);
	CPU_OP_NO(op_no).funct_ptr(cpu);
	cpu->pc += 1;
}

int				main(void)
{
	char		ram[BUFF_SIZE];
	char		registers[REG_LEN];
	t_vcpu		cpu;

	ft_bzero(&ram, BUFF_SIZE);
	ft_bzero(&registers, REG_LEN);

	ram[0] = 0x01;
	ram[1] = 0x01;

	init_cpu(&cpu);
	load_process(&cpu, registers, ram);

	print_memory("Memory   ", ram, BUFF_SIZE);
	print_memory("Registers", registers, REG_LEN);
	print_cpu(&cpu);

	exec_next_instruction(&cpu);
	exec_next_instruction(&cpu);
	exec_next_instruction(&cpu);

	return (0);
}
