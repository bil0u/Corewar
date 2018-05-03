/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:43 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 20:55:06 by upopee           ###   ########.fr       */
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

# define TOU8(x)		(uint8_t)((x) & 0xFF)
# define TOU16(x)		(uint16_t)((x) & 0xFFFF)
# define TOI16(x)		(int16_t)((x) & 0xFFFF)
# define TOU32(x)		(uint32_t)(x)
# define TOI32(x)		(int32_t)(x)

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

# define NB_OPS			16
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
	uint8_t			short_directs;
	t_argtypes		valid_types[NBR_TYPES];
}					t_op;

/*
** -- PROCESSES --
*/

# define REG_NUMBER		16
# define REG_SIZE		4
# define REG_LEN		(REG_NUMBER * REG_SIZE)
# define REG_MAXVALUE	((1UL << (REG_SIZE * CHAR_BIT)) - 1)
# define REG_READ		cpu->memory[jump_to(cpu->pc_copy, cpu->b_read)]

typedef struct		s_process
{
	uint32_t		registers[REG_NUMBER];
	uint32_t		birth;
	uint32_t		last_live;
	uint32_t		pid;
	uint16_t		pc;
	uint16_t		timer;
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

typedef struct s_vmctrl		t_vmctrl;
typedef struct s_jobctrl	t_jobctrl;

# define NEED_ZBUG		(cpu->ctrl->flags & CWF_ZBUG)

typedef struct		s_vcpu
{
	uint32_t		tick;
	uint16_t		pc_copy;
	uint8_t			*memory;
	uint16_t		*m_flags;
	uint32_t		op_args[MAX_ARGS];
	uint8_t			op_bytecode;
	uint8_t			b_read;
	t_jobctrl		*jobs;
	t_vmctrl		*ctrl;
}					t_vcpu;

#endif
