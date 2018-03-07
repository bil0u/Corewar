/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/03/07 05:24:17 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "cpu_types.h"
#include "instructions.h"
#include "cpu.h"

/*
** -- FETCH THE N_TH ARGUMENT
**    > Securely fetch (circular buffer proof) the n_th argument, and return
**      the number of bytes read;
*/

static uint8_t	fetch_next_arg(t_vcpu *cpu, uint64_t *pc_tmp,
								uint8_t arg_no, uint8_t bitmask)
{
	t_arg		*buff;
	uint8_t		arg_type;
	uint8_t		valid_types;

	buff = cpu->args_buff + arg_no;
	valid_types = cpu->curr_instruction->valid_types[arg_no];
	arg_type = (bitmask & 0xC0) >> 6;
	if (arg_type == ARG_REG && (valid_types & T_REG) != 0)
	{
		buff->reg_no = *(cpu->memory + *pc_tmp);
		return (sizeof(buff->reg_no));
	}
	else if (arg_type == ARG_IND && (valid_types & T_IND) != 0)
	{
		secure_fetch(pc_tmp, cpu->memory, (uint8_t *)buff, sizeof(buff->ind));
		return (sizeof(buff->ind));
	}
	else if (arg_type == ARG_DIR && (valid_types & T_DIR) != 0)
	{
		secure_fetch(pc_tmp, cpu->memory, (uint8_t *)buff, sizeof(buff->dir));
		return (sizeof(buff->dir));
	}
	return (0);
}

/*
** -- FETCH THE ARGUMENTS
**    > Fetch the arguments bimask on ARGBC_SIZE bytes
**    > Decode each argument one by one and store them in the vcpu->args_buff
**    > Moves the PC after reading them
**
**    >> Stop reading if there is an error in the instruction arg(s), and set
**       the instruction to NULL
*/

static void		fetch_arguments(t_vcpu *cpu, uint8_t *bytes_read)
{
	uint64_t	pc_tmp;
	uint8_t 	bitmask;
	uint8_t		arg_no;
	uint8_t		arg_sz;

	bitmask = *((uint8_t *)(cpu->memory + jump_to(cpu->pc, *bytes_read)));
	*bytes_read += ARGBC_SIZE;
	arg_no = 0;
	pc_tmp = jump_to(cpu->pc, *bytes_read);
	while (arg_no < cpu->curr_instruction->nb_args)
	{
		if ((arg_sz = fetch_next_arg(cpu, &pc_tmp, arg_no, bitmask)) == 0)
		{
			ft_printf("{red} - Not executed, invalid arguments{eoc}\n");
			cpu->pc = jump_to(cpu->pc, OPBC_SIZE);
			cpu->curr_instruction = &(g_op_set[0]);
			return ;
		}
		ft_printf("f{blue} - Fetched arg #%d [%d byte(s)]{eoc}\n", arg_no + 1, arg_sz);
		*bytes_read += arg_sz;
		bitmask <<= 2;
		++arg_no;
	}
	cpu->pc = pc_tmp;
}

/*
** -- FETCH THE CURRENT INSTRUCTION
** -- Steps of an instruction cycle :
**    > Fetch the instruction on OPBC_SIZE bytes
**    > Decode and check arguments if there is any & the opcode is known
**    > Moves the PC to the next instruction
**    > Execute the instruction if the opcode is known
*/

static uint8_t	fetch_instruction(t_vcpu *cpu)
{
	uint8_t		op_no;
	uint8_t		bytes_read;

	op_no = cpu->memory[cpu->pc];
	cpu->curr_instruction = &(g_op_set[op_no]);
	bytes_read = OPBC_SIZE;
	if (op_no != 0 && op_no < NB_INSTRUCTIONS)
		ft_printf("{yellow}## Fetched instruction %#2.2x : {cyan}'%s'{eoc}\n", op_no, cpu->curr_instruction->name);
	if (op_no && op_no < NB_INSTRUCTIONS && cpu->curr_instruction->nb_args > 0)
		fetch_arguments(cpu, &bytes_read);
	else
		cpu->pc = jump_to(cpu->pc, OPBC_SIZE);
	return (cpu->curr_instruction->op_number);
}

/*
** -- RUN THE CPU FOR NB_CYCLES, OR IN A LOOP IS THE FLAG IS GIVEN
*/

void			run_cpu(t_vcpu *cpu, uint64_t nb_cycles, uint8_t loop, int fd)
{
	uint64_t	cycle_no;
	uint8_t		op_no;

	cycle_no = 1;
	while (cycle_no <= nb_cycles)
	{
		print_memory(NULL, cpu->memory, MEM_SIZE, cpu->pc, fd);
		//print_memory("Registers", registers, REG_LEN, NULL);
		op_no = fetch_instruction(cpu);
		if (op_no != 0 && op_no < NB_INSTRUCTIONS)
		{
			cpu->curr_instruction->funct_ptr(cpu->memory, cpu->registers,
											&cpu->carry, cpu->args_buff);
		}
		++cycle_no;
		loop ? --cycle_no : (void)0;
	}
}

int				main(void)
{
	uint8_t		ram[MEM_SIZE];
	uint8_t		registers[REG_LEN];
	t_vcpu		cpu;
	int			fd;

	ft_bzero(&ram, MEM_SIZE);
	ft_bzero(&registers, REG_LEN);
	init_cpu(&cpu, ram);
	load_process(&cpu, registers, 0);

/*
	ram[1] = 0x01;
	ram[MEM_SIZE - 4] = 0x01;
	ram[MEM_SIZE - 3] = 0xC0;
	cpu.pc = 5;
*/

	ram[0] = 0x01;
	ram[1] = 0x80;
	ram[2] = 0x00;
	ram[3] = 0x00;
	ram[4] = 0x00;
	ram[5] = 0x01;
	ram[20] = 0x01;
	ram[21] = 0x80;
	ram[22] = 0x00;
	ram[23] = 0x00;
	ram[24] = 0x00;
	ram[25] = 0x02;

	fd = 1;
	run_cpu(&cpu, MEM_SIZE * 3, 0, fd);
	return (0);
}
