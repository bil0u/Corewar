/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/03/16 17:34:39 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define NB_INSTRUCTIONS	3

int		live_instr(t_vcpu *cpu);
int		load_instr(t_vcpu *cpu);

t_op    g_op_set[NB_INSTRUCTIONS] =
{
	{"no_op",	0,	0,	NULL,			0,	{0}},
	{"live",	1,	1,	&live_instr,	0,	{T_DIR}},
	{"ld",		2,	2,	&load_instr,	1,	{T_DIR|T_IND, T_REG}}
};

#endif
