/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:41 by upopee            #+#    #+#             */
/*   Updated: 2018/04/24 17:02:56 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_instructions.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"
#include "vm_debug.h"

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
		ARG_DEB ? log_this(ADW, P_ARG_REG, arg_no + 1, *arg_buff) : 0;
	}
	else if (type == ARG_IND)
	{
		secure_fetch(cpu->pc_copy, cpu->memory, arg_buff, ARG_INDSZ);
		ARG_DEB ? log_this(ADW, P_ARG_IND, arg_no + 1, *arg_buff) : 0;
		if (next_op->op_number < 13)
		{
			*arg_buff = (uint32_t)(((int32_t)*arg_buff) % IDX_MOD);
			ARG_DEB ? log_this(ADW, P_IND_MOD, *arg_buff) : 0;
		}
		*arg_buff = jump_to(pending->pc, (int)*arg_buff);
	}
	else if (type == ARG_DIR)
	{
		if (next_op->ind_address)
			type = ARG_IND;
		secure_fetch(cpu->pc_copy, cpu->memory, arg_buff, get_argsize(type));
		ARG_DEB ? log_this(ADW, P_ARG_DIR, arg_no + 1, *arg_buff) : 0;
	}
	return (get_argsize(type));
}

/*
** -- FETCH THE ARGUMENTS
*/

static void		fetch_arguments(t_vcpu *cpu, t_process *pending)
{
	uint8_t		nb_args;
	uint8_t		arg_size;
	uint8_t		arg_no;
	uint8_t		type;

	cpu->pc_copy = jump_to(pending->pc, OPBC_SIZE + ARGBC_SIZE);
	nb_args = pending->next_op->nb_args;
	ARG_DEB ? log_this(ADW, OPBC_OK, nb_args) : 0;
	arg_no = 0;
	while (arg_no < nb_args)
	{
		type = (CPU_OPBC >> (6 - (arg_no << 1))) & 0x03;
		arg_size = fetch_nextarg(cpu, pending, arg_no, type);
		cpu->pc_copy = jump_to(cpu->pc_copy, arg_size);
		++arg_no;
	}
}

/*
** -- CHECK THE SANITY OF BYTECODE AND ARGS
**    > Check if the given bytecode is valid for the current instruction
**    > Increment the value pointed by 'b' pointer of total args size
*/

static uint8_t	sanity_check(t_vcpu *cpu, t_op *op,
							uint8_t *b_read, uint8_t arg_no)
{
	uint8_t		reg_no;
	uint8_t		arg_type;
	uint8_t		valid_types;
	uint8_t		valid_args;

	*b_read += ARGBC_SIZE;
	valid_args = 0;
	while (arg_no < op->nb_args)
	{
		arg_type = (CPU_OPBC >> (6 - (arg_no << 1))) & 0x03;
		valid_types = op->valid_types[arg_no++];
		if ((arg_type == ARG_REG && valid_types & T_REG)
		|| (arg_type == ARG_IND && valid_types & T_IND)
		|| (arg_type == ARG_DIR && valid_types & T_DIR))
		{
			if (arg_type == ARG_REG
			&& ((reg_no = REG_READ) == 0 || reg_no > REG_NUMBER))
				ARG_DEB ? log_this(ADW, REG_KO, arg_no, REG_READ) : 0;
			else
				++valid_args;
		}
		op->ind_address && arg_type == ARG_DIR ? arg_type = ARG_IND : 0;
		*b_read += get_argsize(arg_type);
	}
	return (valid_args == arg_no);
}

/*
** -- EXECUTE THE PENDING INSTRUCTION FOR A GIVEN PROCESS
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
	t_op		*op;
	uint8_t		valid;

	op = pending->next_op;
	cpu->pc_copy = pending->pc;
	cpu->b_read = OPBC_SIZE;
	ARG_DEB ? log_this(ADW, P_CURROP, ADA) : 0;
	valid = TRUE;
	if (op->has_bytecode)
	{
		CPU_OPBC = *(cpu->memory + jump_to(cpu->pc_copy, OPBC_SIZE));
		if ((valid = CPU_OPBC)
		&& (valid = sanity_check(cpu, op, &cpu->b_read, 0)))
			fetch_arguments(cpu, pending);
		else if (ARG_DEB)
			log_this(ADW, OPBC_KO, cpu->b_read);
	}
	valid ? cpu->b_read += op->funct_ptr(cpu, pending, player, game) : 0;
	if (cpu->b_read)
	{
		PC_VERB ? print_pcmove(pending->pc, cpu->memory, cpu->b_read) : 0;
		pending->pc = jump_to(pending->pc, cpu->b_read);
	}
	ARG_DEB ? log_this(ADW, P_SEP) : 0;
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
			MEM_DEB ? debug_memory(MDA, MEM_WIN) : 0;
			return ;
		}
		pending->next_op = &(g_op_set[op_no]);
		pending->timer = pending->next_op->cost;
	}
	if (--pending->timer == 0)
	{
		ft_sprintf(cpu->ctrl->verbose.color_buff[0], get_p_color(pending->player_no));
		exec_op(cpu, pending, player, game);
		MEM_DEB ? debug_memory(MDA, MEM_WIN) : 0;
		pending->next_op = NULL;
	}
}
