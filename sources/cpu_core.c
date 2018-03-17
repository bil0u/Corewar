/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/03/17 20:50:18 by upopee           ###   ########.fr       */
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

static uint8_t	fetch_next_arg(t_vcpu *cpu, uint32_t pc_tmp,
								uint8_t arg_no, uint8_t bytecode)
{
	uint32_t	*buff;
	uint8_t		arg_type;
	uint8_t		valid_types;

	buff = cpu->op_args + arg_no;
	valid_types = cpu->curr_instruction->valid_types[arg_no];
	arg_type = (bytecode & 0xC0) >> 6;
	if (arg_type == ARG_REG && (valid_types & T_REG) != 0)
	{
		buff[0] = *(cpu->memory + pc_tmp);
		log_this("ins", 0, "{green}Arg %hhu:{eoc} [REGISTER] | ({yellow}%#.2x{eoc})\n", arg_no + 1, *buff);
		return (ARG_REGSZ);
	}
	else if (arg_type == ARG_IND && (valid_types & T_IND) != 0)
	{
		secure_fetch(pc_tmp, cpu->memory, buff, ARG_INDSZ);
		log_this("ins", 0, "{green}Arg %hhu:{eoc} [INDIRECT] | ({yellow}%#.2x{eoc})\n", arg_no + 1, *buff);
		return (ARG_INDSZ);
	}
	else if (arg_type == ARG_DIR && (valid_types & T_DIR) != 0)
	{
		secure_fetch(pc_tmp, cpu->memory, buff, ARG_DIRSZ);
		log_this("ins", 0, "{green}Arg %hhu:{eoc} [DIRECT] | ({yellow}%#.2x{eoc})\n", arg_no + 1, *buff);
		return (ARG_DIRSZ);
	}
	else
		log_this("ins", 0, "{red}Arg #%hhu:{eoc} INVALID - STOP READING\n", arg_no + 1);
	return (0);
}

/*
** -- FETCH THE ARGUMENTS
**    > Fetch the arguments bimask on ARGBC_SIZE bytes
**    > Decode each argument one by one and store them in the vcpu->op_args
**
**    >> Stop reading if there is an error in the instruction arg(s), and set
**       the instruction to NULL
*/

static void		fetch_arguments(t_vcpu *cpu, uint8_t *bytes_read)
{
	uint32_t	pc_tmp;
	uint8_t		bytecode;
	uint8_t		arg_no;
	uint8_t		arg_sz;

	bytecode = *((uint8_t *)(cpu->memory + jump_to(cpu->pc, (int)*bytes_read)));
	cpu->op_bytecode = bytecode;
	*bytes_read += ARGBC_SIZE;
	arg_no = 0;
	pc_tmp = jump_to(cpu->pc, (int)*bytes_read);
	while (arg_no < cpu->curr_instruction->nb_args)
	{
		if ((arg_sz = fetch_next_arg(cpu, pc_tmp, arg_no, bytecode)) == 0)
		{
			cpu->curr_instruction = &(g_op_set[0]);
			return ;
		}
		pc_tmp = jump_to(pc_tmp, arg_sz);
		*bytes_read += arg_sz;
		bytecode <<= 2;
		++arg_no;
	}
}

/*
** -- FETCH THE CURRENT INSTRUCTION
*/

static uint8_t	fetch_instruction(t_vcpu *cpu, uint8_t *bytes_read)
{
	uint8_t		op_no;

	op_no = cpu->memory[cpu->pc];
	cpu->curr_instruction = &(g_op_set[op_no]);
	*bytes_read = OPBC_SIZE;
	return (op_no);
}

/*
** -- RUN THE CPU FOR NB_CYCLES, OR IN A LOOP IF THE FLAG IS SET
** -- Steps of an instruction cycle :
**    > Fetch the instruction on OPBC_SIZE bytes
**    > Decode and check arguments if there is any & the opcode is known
**    > Moves the PC to the next instruction
**    > Execute the instruction if the opcode is known
*/

void			run_cpu(t_vcpu *cpu, uint32_t nb_cycles, uint8_t loop)
{
	uint32_t	cycle_no;
	uint8_t		op_no;
	uint8_t		bytes_read;

	cycle_no = 1;
	while (cycle_no <= nb_cycles)
	{
		print_memory(cpu);
		print_registers(cpu);
		op_no = fetch_instruction(cpu, &bytes_read);
		if (op_no != 0 && op_no < NB_INSTRUCTIONS)
		{
			log_this("ins", 0, "{yellow}%s:{eoc}\n", cpu->curr_instruction->name);
			if (cpu->curr_instruction->has_bytecode)
				fetch_arguments(cpu, &bytes_read);
			bytes_read += cpu->curr_instruction->funct_ptr(cpu);
			log_this("ins", 0, "----\n");
		}
		cpu->pc = jump_to(cpu->pc, bytes_read);
		loop ? (void)0 : ++cycle_no;
		sleep(1);
	}
}

int				main(void)
{
	uint8_t		ram[MEM_SIZE];
	uint32_t	registers[REG_NUMBER];
	t_vcpu		cpu;

	ft_bzero(&ram, MEM_SIZE);
	ft_bzero(&registers, REG_LEN);
	ft_bzero(&cpu, sizeof(cpu));

	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);

	ram[0] = 0x01;
	ram[1] = 0x00;
	ram[2] = 0x00;
	ram[3] = 0x00;
	ram[4] = 0x01;

	ram[6] = 0x02;
	ram[7] = 0xD0;
	ram[8] = 0x00;
	ram[9] = 0x01;
	ram[10] = 0x02;

	ram[12] = 0x03;
	ram[13] = 0x50;
	ram[14] = 0x02;
	ram[15] = 0x07;

	ram[17] = 0x03;
	ram[18] = 0x70;
	ram[19] = 0x07;
	ram[20] = 0x00;
	ram[21] = 0x08;



	init_cpu(&cpu, ram);
	load_process(&cpu, registers, 0);
	run_cpu(&cpu, 10, 1);

	return (0);
}
