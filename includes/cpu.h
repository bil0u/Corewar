/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:07:43 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 03:47:54 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H

# include <stddef.h>
# include <stdint.h>

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

typedef union	u_args
{
	uint16_t	u16;
	uint32_t	u32;
	void		*ptr;
}				t_args;

/*
**	-------- VIRTUAL CPU STRUCTURE AND MACROS ---------
*/

# define REG_NUMBER		16
# define REG_SIZE		4
# define REG_LEN		(REG_NUMBER * REG_SIZE)

# define CPU_PC(cpu) ((cpu)->pc)
# define CPU_CARRY(cpu) ((cpu)->carry)
# define CPU_REGS(cpu) ((cpu)->registers)
# define CPU_REG_NO(cpu, reg_no) (*(CPU_REGS(cpu) + (reg_no * REG_SIZE)))
# define CPU_ARGS(cpu) ((cpu)->args_buff)
# define CPU_ARG_NO(cpu, arg_no) (CPU_ARGS(cpu)[arg_no])
# define CPU_OP_NO(op_no) (g_op_set[op_no])

typedef struct		s_vcpu
{
	void			*pc;
	void			*registers;
	t_args			args_buff[MAX_ARGS];
	unsigned int	carry : 1;
}					t_vcpu;

/*
**	-------- OPERATIONS STRUCTURE AND MACROS ---------
*/


typedef void	(*t_instr)(t_vcpu *cpu);

typedef struct		s_op
{
	char			*name;
	uint8_t			op_number;
	uint8_t			nb_args;
	uint8_t			args_mask[MAX_ARGS];
	t_instr			funct_ptr;
}					t_op;

/*
**	-------- _DEBUG_ ---------
*/

void	print_memory(char *name, char *s, uint32_t len);
void	print_cpu(t_vcpu *cpu);

#endif
