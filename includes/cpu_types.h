/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:43 by upopee            #+#    #+#             */
/*   Updated: 2018/03/26 23:32:40 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_TYPES_H
# define CPU_TYPES_H

# include <stddef.h>
# include <stdint.h>

/*
**	-------- TMP ---------
*/

# define MEM_SIZE		40				// TEST VALUE - TO BE MODIFIED
# define IDX_MOD		MEM_SIZE		// TEST VALUE - TO BE MODIFIED
# define MAX_PLAYERS	4

/*
**	-------- ARGUMENTS  ---------
*/

# define ARGBC_SIZE	1
# define MAX_ARGS	4
# define NBR_TYPES	4

# define T_REG		0b0001
# define T_DIR		0b0010
# define T_IND		0b0100
# define T_LAB		0b1000

# define ARG_REG	0b01
# define ARG_DIR	0b10
# define ARG_IND	0b11
# define ARG_REGSZ	1
# define ARG_INDSZ	2
# define ARG_DIRSZ	4

typedef uint8_t		t_argtypes;

/*
**	-------- INSTRUCTIONS ---------
*/

# define OPBC_SIZE	1

typedef struct		s_vcpu t_vcpu;
typedef int			(*t_instr)(t_vcpu *cpu);

typedef struct		s_op
{
	char			*name;
	t_instr			funct_ptr;
	uint8_t			op_number;
	uint8_t			nb_args;
	uint8_t			has_bytecode;
	uint8_t			ind_address;
	t_argtypes		valid_types[NBR_TYPES];
}					t_op;

/*
**	-------- VIRTUAL CPU ---------
**
**  pc					->	index (in memory) of next instruction to be exec.
**  op_args				->	buffer where arguments are stored before exec.
**  curr_instruction	->	points to the current t_op structure
**  registers			->	points to the current process registers
**  memory				->	points to the processes shared memory
**  carry				->	flag modified by certains instructions
**  op_bytecode			->	byte where the current op bytecode is stored
*/

# define REG_NUMBER	8
# define REG_SIZE	4
# define REG_LEN	(REG_NUMBER * REG_SIZE)

typedef struct		s_vcpu
{
	uint32_t		pc;
	uint32_t		op_args[MAX_ARGS];
	t_op			*curr_instruction;
	uint32_t		*registers;
	uint8_t			*memory;
	uint8_t			carry;
	uint8_t			op_bytecode;
}					t_vcpu;

#endif
