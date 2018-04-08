/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/04/08 07:42:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "instructions.h"
#include "cpu.h"
#include "corewar.h"
#include "cpu_verbose.h"

/*
** -- FETCH THE CURRENT INSTRUCTION
*/

static uint8_t	fetch_instruction(t_vcpu *cpu, uint8_t *bytes_read)
{
	uint8_t		op_no;

	op_no = cpu->memory[cpu->pc[0]];
	cpu->curr_instruction = &(g_op_set[op_no]);
	*bytes_read = OPBC_SIZE;
	return (op_no);
}

/*
** -- FETCH THE N_TH ARGUMENT
**    > Securely fetch (circular buffer proof) the n_th argument, and return
**      the number of bytes read;
**    > Convert
*/

static uint8_t	fetch_nextarg(t_vcpu *cpu, uint32_t pc_tmp,
								uint8_t arg_no, uint8_t arg_type)
{
	uint32_t	*arg_buff;

	arg_buff = cpu->op_args + arg_no;
	if (arg_type == ARG_REG && ((*arg_buff = *(cpu->memory + pc_tmp)) || 1))
		log_this("ins", 0, P_ARG_REG, arg_no + 1, *arg_buff);
	else if (arg_type == ARG_IND)
	{
		secure_fetch(pc_tmp, cpu->memory, arg_buff, ARG_INDSZ);
		log_this("ins", 0, P_ARG_IND, arg_no + 1, *arg_buff);
		if (cpu->curr_instruction->op_number < 13)
		{
			*arg_buff = (uint32_t)((int16_t)(*arg_buff & 0xFFFF) % IDX_MOD);
			log_this("ins", 0, P_IND_MOD, *arg_buff);
		}
		*arg_buff = jump_to(cpu->pc[0], (int)*arg_buff);
	}
	else if (arg_type == ARG_DIR)
	{
		if (cpu->curr_instruction->ind_address)
			arg_type = ARG_IND;
		secure_fetch(pc_tmp, cpu->memory, arg_buff, get_argsize(arg_type));
		log_this("ins", 0, P_ARG_DIR, arg_no + 1, *arg_buff);
	}
	return (get_argsize(arg_type));
}

/*
** -- CHECK THE SANITY OF ARGS BYTECODE
**    > Check if the given bytecode is valid for the current instruction
**    > Increment the value pointed by 'bytes_read' pointer of total args size
*/

static uint8_t	sanity_check(t_op *op, uint8_t bytecode, uint8_t *bytes_read)
{
	uint8_t		arg_no;
	uint8_t		arg_type;
	uint8_t		valid_types;
	uint8_t		valid_args;

	if (bytecode == 0)
		return (0);
	valid_args = 0;
	arg_no = 0;
	while (arg_no < op->nb_args)
	{
		arg_type = (bytecode >> (6 - (arg_no << 1))) & 0x03;
		valid_types = op->valid_types[arg_no];
		if ((arg_type == ARG_REG && valid_types & T_REG)
		|| (arg_type == ARG_IND && valid_types & T_IND)
		|| (arg_type == ARG_DIR && valid_types & T_DIR))
			++valid_args;
		if (op->ind_address && arg_type == ARG_DIR)
			arg_type = ARG_IND;
		*bytes_read += get_argsize(arg_type);
		++arg_no;
	}
	return (valid_args == arg_no);
}

/*
** -- FETCH THE ARGUMENTS
**    > Fetch the arguments bytecode on ARGBC_SIZE bytes
**    > If the sanity check is successful :
**      > Decode each argument one by one and store them in the vcpu->op_args
**    > Otherwise :
*/

static void		fetch_arguments(t_vcpu *cpu, uint8_t *bytes_rd, uint8_t *valid)
{
	uint32_t	pc_tmp;
	uint8_t		bytecode;
	uint8_t		arg_no;
	uint8_t		arg_sz;

	bytecode = *(cpu->memory + jump_to(cpu->pc[0], OPBC_SIZE));
	if ((*valid = sanity_check(cpu->curr_instruction, bytecode, bytes_rd)) != 0)
	{
		*bytes_rd += ARGBC_SIZE;
		cpu->op_bytecode = bytecode;
		pc_tmp = jump_to(cpu->pc[0], OPBC_SIZE + ARGBC_SIZE);
		arg_no = 0;
		log_this("ins", 0, P_ARG_OK, cpu->curr_instruction->nb_args);
		while (arg_no < cpu->curr_instruction->nb_args)
		{
			arg_sz = (bytecode >> (6 - (arg_no << 1))) & 0x03;
			arg_sz = fetch_nextarg(cpu, pc_tmp, arg_no, arg_sz);
			pc_tmp = jump_to(pc_tmp, arg_sz);
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

void			exec_instruction(t_vcpu *cpu)
{
	t_op		*op;
	uint8_t		op_no;
	uint8_t		bytes_read;
	uint8_t		valid;

	op_no = fetch_instruction(cpu, &bytes_read);
	if (op_no != 0 && op_no < NB_INSTRUCTIONS)
	{
		op = cpu->curr_instruction;
		log_this("ins", 0, P_CURR_OP, op->op_number, op->name, cpu->pc[0]);
			valid = TRUE;
		if (op->has_bytecode)
			fetch_arguments(cpu, &bytes_read, &valid);
		if (valid)
			bytes_read += op->funct_ptr(cpu);
			log_this("ins", 0, "----\n");
	}
	cpu->pc[0] = jump_to(cpu->pc[0], bytes_read);
}
