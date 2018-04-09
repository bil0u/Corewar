/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:43 by upopee            #+#    #+#             */
/*   Updated: 2018/04/09 07:15:39 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_TYPES_H
# define CPU_TYPES_H

# include <stddef.h>
# include <stdint.h>

/*
**	-- ARGUMENTS  --
*/

# define ARGBC_SIZE	1
# define MAX_ARGS	4
# define NBR_TYPES	4

# define T_REG		(1 << 0)
# define T_DIR		(1 << 1)
# define T_IND		(1 << 2)
# define T_LAB		(1 << 3)

# define ARG_REG	0b01
# define ARG_DIR	0b10
# define ARG_IND	0b11
# define ARG_REGSZ	1
# define ARG_INDSZ	2
# define ARG_DIRSZ	4

typedef uint8_t		t_argtypes;

/*
**	-- INSTRUCTIONS --
*/

# define OPBC_SIZE	1
# define NB_OPS		17

typedef struct		s_vcpu t_vcpu;
typedef struct		s_vcpudata t_vcpudata;
typedef int			(*t_instr)(t_vcpu*, t_vcpudata*);

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
**	-- VIRTUAL CPU --
*/

typedef struct		s_vcpudata
{
	t_list			*child_process;
	uint32_t		*nb_processes;
	uint32_t		*tot_processes;
	uint32_t		*last_live;
	uint8_t			*last_alive;
	uint32_t		op_args[MAX_ARGS];
	uint8_t			op_bytecode;
}					t_vcpudata;

typedef struct		s_vcpu
{
	uint64_t		tick;
	uint32_t		*pc;
	uint32_t		*registers;
	uint8_t			*carry;
	uint8_t			*memory;
	t_op			*curr_op;
	t_vcpudata		data;
}					t_vcpu;

#endif
