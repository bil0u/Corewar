/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 04:02:37 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

# include "cpu.h"

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define INSTR_NUMBER	3

void	no_instr(t_vcpu *cpu);
void	live_instr(t_vcpu *cpu);
void	load_instr(t_vcpu *cpu);

t_op    g_op_set[INSTR_NUMBER] =
{
	{"no_op",		0,	0,	{0},					&no_instr},
	{"live",	1,	1,	{T_DIR},					&live_instr},
	{"ld",		2,	2,	{T_DIR|T_IND, T_REG},		&load_instr}
};

#endif
