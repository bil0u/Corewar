/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:43 by upopee            #+#    #+#             */
/*   Updated: 2018/04/23 05:12:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_TYPES_H
# define CPU_TYPES_H

# include <stddef.h>
# include <stdint.h>

/*
**	-- ARGUMENTS  --
*/

# define ARGBC_SIZE		1
# define MAX_ARGS		4
# define NBR_TYPES		4

# define T_REG			(1 << 0)
# define T_DIR			(1 << 1)
# define T_IND			(1 << 2)
# define T_LAB			(1 << 3)

# define ARG_REG		0b01
# define ARG_DIR		0b10
# define ARG_IND		0b11
# define ARG_REGSZ		1
# define ARG_INDSZ		2
# define ARG_DIRSZ		4

typedef uint8_t		t_argtypes;

/*
**	-- INSTRUCTIONS --
*/

# define OPBC_SIZE		1

typedef int			(*t_instr)();

typedef struct		s_op
{
	char			*name;
	t_instr			funct_ptr;
	uint16_t		cost;
	uint8_t			op_number;
	uint8_t			nb_args;
	uint8_t			has_bytecode;
	uint8_t			ind_address;
	t_argtypes		valid_types[NBR_TYPES];
}					t_op;

/*
** -- PROCESSES --
*/

# define REG_NUMBER		16
# define REG_SIZE		4
# define REG_LEN		(REG_NUMBER * REG_SIZE)
# define REG_MAXVALUE	((1UL << (REG_SIZE * CHAR_BIT)) - 1)

typedef struct			s_process
{
	uint32_t		pid;
	uint32_t		registers[REG_NUMBER];
	uint32_t		pc;
	uint32_t		timer;
	uint32_t		last_live;
	uint8_t			carry;
	uint8_t			player_no;
	t_op			*next_op;
}					t_process;

/*
**	-- VIRTUAL CPU --
*/

# define CPU_ARG		cpu->op_args
# define CPU_OPBC		cpu->op_bytecode
# define CPU_MEM		cpu->memory

typedef struct		s_vmctrl t_vmctrl;
typedef struct		s_jobctrl t_jobctrl;

typedef struct		s_vcpu
{
	uint32_t		tick;
	uint32_t		pc_copy;
	uint8_t			*memory;
	uint32_t		op_args[MAX_ARGS];
	uint8_t			op_bytecode;
	uint8_t			b_read;
	t_jobctrl		*jobs;
	t_vmctrl		*ctrl;
}					t_vcpu;

#endif
