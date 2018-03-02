/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:43 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 16:50:33 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_TYPES_H
# define CPU_TYPES_H

# include <stddef.h>
# include <stdint.h>

/*
**	-------- TMP ---------
*/

# define MEM_SIZE 32

/*
**	-------- ALLOWED ARGS STRUCTURE AND MACROS ---------
**	registers	-> ptr
**	directs 	-> u32
**	indirects	-> u16
*/

# define MAX_ARGS		4

# define T_REG			1
# define T_DIR			2
# define T_IND			4
# define T_LAB			8

# define ARG_REG		0x01
# define ARG_DIR		0x02
# define ARG_IND		0x03

typedef union	u_arg
{
	uint16_t	ind;
	uint32_t	dir;
	void		*reg;
}				t_arg;

/*
**	-------- OPERATIONS STRUCTURE AND MACROS ---------
*/

typedef void	(*t_instr)(uint8_t *memory, uint8_t *registers,
								uint8_t *carry, t_arg *args);

typedef struct		s_op
{
	char			*name;
	uint8_t			op_number;
	uint8_t			nb_args;
	t_instr			funct_ptr;
}					t_op;

/*
**	-------- VIRTUAL CPU STRUCTURE AND MACROS ---------
*/

# define REG_NUMBER		16
# define REG_SIZE		4
# define REG_LEN		(REG_NUMBER * REG_SIZE)

/*
# define CPU_PC(cpu) ((cpu)->pc)
# define CPU_CARRY(cpu) ((cpu)->carry)
# define CPU_REGS(cpu) ((cpu)->registers)
# define CPU_REG_NO(cpu, reg_no) (*(CPU_REGS(cpu) + (reg_no * REG_SIZE)))
# define CPU_ARGS(cpu) ((cpu)->args_buff)
# define CPU_ARG_NO(cpu, arg_no) (CPU_ARGS(cpu)[arg_no])
# define CPU_OP_NO(op_no) (g_op_set[op_no])
*/

typedef struct		s_vcpu
{
	void			*pc;
	void			*registers;
	t_arg			args_buff[MAX_ARGS];
	t_op			*curr_instruction;
	uint8_t			carry;
}					t_vcpu;

#endif
