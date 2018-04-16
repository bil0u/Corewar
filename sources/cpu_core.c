/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 13:33:37 by upopee           ###   ########.fr       */
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
#include "cpu.h"
#include "corewar.h"
#include "cpu_verbose.h"
#include "instructions.h"

/*
** -- FETCH THE N_TH ARGUMENT
**    > Securely fetch (circular buffer proof) the n_th argument, and return
**      the number of bytes read;
**    > Apply the IDX MOD for indirect args if the op is restricted
**    > Fetch directs on 2 bytes if the op ind_address's flag is set
*/

static uint8_t	fetch_nextarg(t_vcpu *cpu, t_process *pending,
								uint8_t arg_no, uint8_t type)
{
	t_op		*next_op;
	uint32_t	*arg_buff;

	arg_buff = cpu->op_args + arg_no;
	next_op = pending->next_op;
	if (type == ARG_REG)
	{
		*arg_buff = *(cpu->memory + cpu->pc_copy);
		// log_this("ins", 0, P_ARG_REG, arg_no + 1, *arg_buff);
	}
	else if (type == ARG_IND)
	{
		secure_fetch(cpu->pc_copy, cpu->memory, arg_buff, ARG_INDSZ);
		// log_this("ins", 0, P_ARG_IND, arg_no + 1, *arg_buff);
		if (next_op->op_number < 13)
		{
			*arg_buff = (uint32_t)(((int32_t)*arg_buff) % IDX_MOD);
			// log_this("ins", 0, P_IND_MOD, *arg_buff);
		}
		*arg_buff = jump_to(pending->pc, (int)*arg_buff);
	}
	else if (type == ARG_DIR)
	{
		if (next_op->ind_address)
			type = ARG_IND;
		secure_fetch(cpu->pc_copy, cpu->memory, arg_buff, get_argsize(type));
		// log_this("ins", 0, P_ARG_DIR, arg_no + 1, *arg_buff);
	}
	return (get_argsize(type));
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
*/

static uint8_t	fetch_arguments(t_vcpu *cpu, t_process *pending, uint8_t opbc)
{
	uint8_t		nb_args;
	uint8_t		bytes_read;
	uint8_t		arg_no;
	uint8_t		type;

	cpu->op_bytecode = opbc;
	cpu->pc_copy = jump_to(pending->pc, OPBC_SIZE + ARGBC_SIZE);
	nb_args = pending->next_op->nb_args;
	arg_no = 0;
	// log_this("ins", 0, P_ARG_OK, nb_args);
	while (arg_no < nb_args)
	{
		type = (opbc >> (6 - (arg_no << 1))) & 0x03;
		bytes_read = fetch_nextarg(cpu, pending, arg_no, type);
		cpu->pc_copy = jump_to(cpu->pc_copy, bytes_read);
		++arg_no;
	}
	return (ARGBC_SIZE);
}

/*
** -- EXECUTE THE PENDING INSTRUCTION FOR THE PREVIOUSLY LOADED PROCESS
** -- Steps of an instruction cycle :
**    > Fetch the instruction on OPBC_SIZE bytes
**     (just before this function call for implementation reasons)
**    > If the op_code is valid :
**       > Fetch & decode arguments if there is an ocp and ocp is valid
**       > Execute the instruction (unless ocp, if there is one, is invalid)
**    > Moves the PC to the next instruction
**     (bytes_read equals the number of bytes described by the
**      op_bytecode, even if not valid.
**      If there's no opbc, then bytes_read equals OPBC_SIZE)
*/

static void		exec_op(t_vcpu *cpu, t_process *pending,
							t_player *player, t_gamectrl *game)
{
	uint8_t		opbc;
	uint8_t		b_read;
	uint8_t		valid;

	b_read = OPBC_SIZE;
	// log_this("ins", 0, P_CURR_OP, op->op_number, op->name, pending->pc);
	valid = TRUE;
	if (pending->next_op->has_bytecode)
	{
		opbc = *(cpu->memory + jump_to(pending->pc, OPBC_SIZE));
		if ((valid = sanity_check(pending->next_op, opbc, &b_read)))
			b_read += fetch_arguments(cpu, pending, opbc);
		// else
			// log_this("ins", 0, P_ARG_KO, *bytes_rd);
	}
	if (valid)
		b_read += pending->next_op->funct_ptr(cpu, pending, player, game);
	// log_this("ins", 0, P_SEP);
	pending->pc = jump_to(pending->pc, b_read);
}

/*
** -- PERFORMS A EXECUTION STEP FOR THE GIVEN PROCESS
** -- If current process's next_op is set to NULL :
**    > Fetch the instruction on OPBC_SIZE bytes from PC pos in arena
**    > Set the timer to fetched instruction's cycles costs value
** -- Decrements the timer
** -- If decremented timer equals zero :
**    > Launch the intruction execution, and set next_op to NULL
*/

void			exec_or_wait(t_vcpu *cpu, t_process *pending,
								t_player *player, t_gamectrl *game)
{
	uint8_t		op_no;

	if (pending->next_op == NULL)
	{
		if ((op_no = cpu->memory[pending->pc]) == 0 || op_no-- > NB_OPS)
		{
			pending->pc = jump_to(pending->pc, OPBC_SIZE);
			return ;
		}
		pending->next_op = &(g_op_set[op_no]);
		pending->timer = pending->next_op->cost;
	}
	if (--pending->timer == 0)
	{
		exec_op(cpu, pending, player, game);
		pending->next_op = NULL;
		print_memory(cpu->memory, cpu->jobs->p_stack, "mem");
	}
}
