/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/03/22 17:39:06 by upopee           ###   ########.fr       */
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
#include "cpu_verbose.h"

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
** -- FETCH THE N_TH ARGUMENT
**    > Securely fetch (circular buffer proof) the n_th argument, and return
**      the number of bytes read;
*/

static uint8_t	fetch_nextarg(t_vcpu *cpu, uint32_t pc_tmp,
								uint8_t arg_no, uint8_t arg_type)
{
	uint32_t	*buff;

	buff = cpu->op_args + arg_no;
	if (arg_type == ARG_REG)
	{
		buff[0] = *(cpu->memory + pc_tmp);
		log_this("ins", 0, P_ARG_REG, arg_no + 1, *buff);
		return (ARG_REGSZ);
	}
	else if (arg_type == ARG_IND)
	{
		secure_fetch(pc_tmp, cpu->memory, buff, ARG_INDSZ);
		log_this("ins", 0, P_ARG_IND, arg_no + 1, *buff);
		return (ARG_INDSZ);
	}
	else if (arg_type == ARG_DIR)
	{
		secure_fetch(pc_tmp, cpu->memory, buff, ARG_DIRSZ);
		log_this("ins", 0, P_ARG_DIR, arg_no + 1, *buff);
		return (ARG_DIRSZ);
	}
	return (0);
}

/*
** -- CHECK THE SANITY OF ARGS BYTECODE
*/

static uint8_t	sanity_check(t_op *op, uint8_t bytecode, uint8_t *bytes_read)
{
	uint8_t		arg_no;
	uint8_t		arg_type;
	uint8_t		valid_types;
	uint8_t		valid_args;

	valid_args = 0;
	arg_no = 0;
	while (arg_no < op->nb_args)
	{
		arg_type = (bytecode & 0xC0) >> 6;
		valid_types = op->valid_types[arg_no];
		if (arg_type == ARG_REG && valid_types & T_REG)
			++valid_args;
		else if (arg_type == ARG_IND && valid_types & T_IND)
			++valid_args;
		else if (arg_type == ARG_DIR && valid_types & T_DIR)
			++valid_args;
		*bytes_read += get_argsize(arg_type);
		bytecode <<= 2;
		++arg_no;
	}
	return (valid_args == arg_no);
}

/*
** -- FETCH THE ARGUMENTS
**    > Fetch the arguments bytecode on ARGBC_SIZE bytes
**    > If the sanity check is successful :
**      > Decode each argument one by one and store them in the vcpu->op_args
*/

static void		fetch_arguments(t_vcpu *cpu, uint8_t *bytes_rd, uint8_t *valid)
{
	uint32_t	pc_tmp;
	uint8_t		bytecode;
	uint8_t		arg_no;
	uint8_t		arg_sz;

	bytecode = *(cpu->memory + jump_to(cpu->pc, OPBC_SIZE));
	*bytes_rd += ARGBC_SIZE;
	*valid = sanity_check(cpu->curr_instruction, bytecode, bytes_rd);
	if (*valid)
	{
		log_this("ins", 0, P_ARG_OK, cpu->curr_instruction->nb_args);
		cpu->op_bytecode = bytecode;
		pc_tmp = jump_to(cpu->pc, OPBC_SIZE + ARGBC_SIZE);
		arg_no = 0;
		while (arg_no < cpu->curr_instruction->nb_args)
		{
			arg_sz = fetch_nextarg(cpu, pc_tmp, arg_no, (bytecode & 0xC0) >> 6);
			pc_tmp = jump_to(pc_tmp, arg_sz);
			bytecode <<= 2;
			++arg_no;
		}
	}
	else
		log_this("ins", 0, P_ARG_KO, *bytes_rd);
}

/*
** -- RUN THE CPU FOR NB_CYCLES, OR IN A LOOP IF THE FLAG IS SET
** -- Steps of an instruction cycle :
**    > Fetch the instruction on OPBC_SIZE bytes
**    > If the op_code is valid :
**       > Fetch & decode arguments if there is an ocp
**       > Execute the instruction
**    > Moves the PC to the next instruction
*/

void			run_cpu(t_vcpu *cpu, uint32_t nb_cycles, char loop, char slow, char clean)
{
	uint32_t	cycle_no;
	uint8_t		op_no;
	uint8_t		bytes_read;
	uint8_t		valid;

	cycle_no = 1;
	while (cycle_no <= nb_cycles)
	{
		print_memory(cpu, clean);

		op_no = fetch_instruction(cpu, &bytes_read);
		if (op_no != 0 && op_no < NB_INSTRUCTIONS)
		{
			log_this("ins", 0, P_OPNAME, cpu->curr_instruction->name);

			valid = TRUE;
			if (cpu->curr_instruction->has_bytecode)
				fetch_arguments(cpu, &bytes_read, &valid);
			if (valid == TRUE)
				bytes_read += cpu->curr_instruction->funct_ptr(cpu);

			log_this("ins", 0, "----\n");
		}
		cpu->pc = jump_to(cpu->pc, bytes_read);

		print_registers(cpu, clean);

		loop ? (void)0 : ++cycle_no;
		slow ? sleep(1) : (void)0;
	}
}

static void		set_test_values(t_vcpu *cpu, uint8_t *memory)
{
	(void)memory;
	(void)cpu;
	//	TEST LIVE
	// memory[0] = 0x01;
	// memory[1] = 0x00;
	// memory[2] = 0x00;
	// memory[3] = 0x00;
	// memory[4] = 0x01;

	//	TEST LOAD [IND][REG]
	memory[6] = 0x02;
	memory[7] = 0b11010000;
	memory[8] = 0x00;
	memory[9] = 0x01;
	memory[10] = 0x02;

	//	TEST LOAD [DIR][REG]
	// memory[4] = 0x02;
	// memory[5] = 0b10010000;
	// memory[6] = 0x00;
	// memory[7] = 0x00;
	// memory[8] = 0xca;
	// memory[9] = 0xfe;
	// memory[10] = 0x02;

	//	TEST STORE [REG][REG]
	// memory[12] = 0x03;
	// memory[13] = 0b01010000;
	// memory[14] = 0x02;
	// memory[15] = 0x07;

	//	TEST STORE [REG][IND]
	// memory[17] = 0x03;
	// memory[18] = 0b01110000;
	// memory[19] = 0x07;
	// memory[20] = 0x00;
	// memory[21] = 0x08;

	//	TEST ADD [REG][REG][REG]
		// LOAD DIRECT
		// memory[1] = 0x02;
		// memory[2] = 0b10010000;
		// memory[3] = 0x00;
		// memory[4] = 0x00;
		// memory[5] = 0x00;
		// memory[6] = 0x05;
		// memory[7] = 0x01;
		// LOAD DIRECT
	// 	memory[9] = 0x02;
	// 	memory[10] = 0b10010000;
	// 	memory[11] = 0x00;
	// 	memory[12] = 0x00;
	// 	memory[13] = 0x00;
	// 	memory[14] = 0x04;
	// 	memory[15] = 0x02;
	// memory[17] = 0x04;
	// memory[18] = 0b01010100;
	// memory[19] = 0x01;
	// memory[20] = 0x02;
	// memory[21] = 0x03;

	//	TEST SUB [REG][REG][REG]
		// LOAD DIRECT
		// memory[1] = 0x02;
		// memory[2] = 0b10010000;
		// memory[3] = 0x00;
		// memory[4] = 0x00;
		// memory[5] = 0x00;
		// memory[6] = 0x05;
		// memory[7] = 0x01;
		// LOAD DIRECT
	// 	memory[9] = 0x02;
	// 	memory[10] = 0b10010000;
	// 	memory[11] = 0x00;
	// 	memory[12] = 0x00;
	// 	memory[13] = 0x00;
	// 	memory[14] = 0x09;
	// 	memory[15] = 0x02;
	// memory[17] = 0x05;
	// memory[18] = 0b01010100;
	// memory[19] = 0x01;
	// memory[20] = 0x02;
	// memory[21] = 0x03;

	//	TEST AND [REG][REG][REG]
		// LOAD DIRECT
		// memory[1] = 0x02;
		// memory[2] = 0b10010000;
		// memory[3] = 0x00;
		// memory[4] = 0x00;
		// memory[5] = 0x00;
		// memory[6] = 0x01;
		// memory[7] = 0x01;
		// LOAD DIRECT
	// 	memory[9] = 0x02;
	// 	memory[10] = 0b10010000;
	// 	memory[11] = 0x00;
	// 	memory[12] = 0x00;
	// 	memory[13] = 0x00;
	// 	memory[14] = 0x03;
	// 	memory[15] = 0x02;
	// memory[17] = 0x06;
	// memory[18] = 0b01010100;
	// memory[19] = 0x01;
	// memory[20] = 0x02;
	// memory[21] = 0x03;

	//	TEST AND [DIR][IND][REG]
	// memory[2] = 0x06;
	// memory[3] = 0b10110100;
	// memory[4] = 0x00;
	// memory[5] = 0x00;
	// memory[6] = 0x00;
	// memory[7] = 0x02;
	// memory[8] = 0x00;
	// memory[9] = 0x00;
	// memory[10] = 0x03;

	//	TEST OR [REG][REG][REG]
		// LOAD DIRECT
		// memory[1] = 0x02;
		// memory[2] = 0b10010000;
		// memory[3] = 0x00;
		// memory[4] = 0x00;
		// memory[5] = 0x00;
		// memory[6] = 0x01;
		// memory[7] = 0x01;
		// LOAD DIRECT
		// memory[9] = 0x02;
		// memory[10] = 0b10010000;
		// memory[11] = 0x00;
		// memory[12] = 0x00;
		// memory[13] = 0x00;
		// memory[14] = 0x02;
		// memory[15] = 0x02;
	// memory[17] = 0x07;
	// memory[18] = 0b01010100;
	// memory[19] = 0x01;
	// memory[20] = 0x02;
	// memory[21] = 0x03;

	//	TEST OR [DIR][IND][REG]
	// memory[2] = 0x07;
	// memory[3] = 0b10110100;
	// memory[4] = 0x00;
	// memory[5] = 0x00;
	// memory[6] = 0x00;
	// memory[7] = 0x01;
	// memory[8] = 0x00;
	// memory[9] = 0x00;
	// memory[10] = 0x03;

	//	TEST XOR [REG][REG][REG]
		// LOAD DIRECT
		// memory[1] = 0x02;
		// memory[2] = 0b10010000;
		// memory[3] = 0x00;
		// memory[4] = 0x00;
		// memory[5] = 0x00;
		// memory[6] = 0x03;
		// memory[7] = 0x01;
		// LOAD DIRECT
	// 	memory[9] = 0x02;
	// 	memory[10] = 0b10010000;
	// 	memory[11] = 0x00;
	// 	memory[12] = 0x00;
	// 	memory[13] = 0x00;
	// 	memory[14] = 0x02;
	// 	memory[15] = 0x02;
	// memory[17] = 0x08;
	// memory[18] = 0b01010100;
	// memory[19] = 0x01;
	// memory[20] = 0x02;
	// memory[21] = 0x03;

	//	TEST XOR [DIR][IND][REG]
	// memory[2] = 0x08;
	// memory[3] = 0b10110100;
	// memory[4] = 0x00;
	// memory[5] = 0x00;
	// memory[6] = 0x00;
	// memory[7] = 0x03;
	// memory[8] = 0x00;
	// memory[9] = 0x00;
	// memory[10] = 0x03;

	//	TEST ZJMP [DIR]
	// cpu->carry = 1;
	// memory[20] = 0x09;
	// *((uint32_t *)(memory + 21)) = SWAP_UINT32((uint32_t)-15);


}

int				main(void)
{
	uint8_t		memory[MEM_SIZE];
	uint32_t	registers[REG_NUMBER];
	t_vcpu		cpu;

	ft_bzero(&memory, MEM_SIZE);
	ft_bzero(&registers, REG_LEN);
	ft_bzero(&cpu, sizeof(cpu));

	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);

	init_cpu(&cpu, memory);
	set_test_values(&cpu, memory);
	load_process(&cpu, registers, 0);
	run_cpu(&cpu, 10, 1, 1, 1);

	return (0);
}
