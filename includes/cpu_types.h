/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:43 by upopee            #+#    #+#             */
/*   Updated: 2018/03/17 20:48:37 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_TYPES_H
# define CPU_TYPES_H

# include <stddef.h>
# include <stdint.h>

/*
**	-------- TMP ---------
*/

# define MEM_SIZE		32
# define IDX_MOD		15	//(MEM_SIZE / 8)
# define MAX_PLAYERS	4

/*
**	-------- ALLOWED ARGS STRUCTURE AND MACROS ---------
**	registers	-> ptr
**	directs 	-> u32
**	indirects	-> u16
*/

# define MAX_ARGS	4
# define ARGBC_SIZE	1
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
**	-------- OPERATIONS STRUCTURE AND MACROS ---------
*/

# define OPBC_SIZE	1

typedef struct		s_vcpu t_vcpu;
typedef int			(*t_instr)(t_vcpu *cpu);

typedef struct		s_op
{
	char			*name;
	uint8_t			op_number;
	uint8_t			nb_args;
	t_instr			funct_ptr;
	uint8_t			has_bytecode;
	t_argtypes		valid_types[NBR_TYPES];
}					t_op;

/*
**	-------- VIRTUAL CPU STRUCTURE AND MACROS ---------
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
