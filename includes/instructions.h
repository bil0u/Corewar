/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/03/17 18:29:36 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define NB_INSTRUCTIONS	4

int		live_instr(t_vcpu *cpu);
int		load_instr(t_vcpu *cpu);
int		store_instr(t_vcpu *cpu);

t_op    g_op_set[NB_INSTRUCTIONS] =
{
//	OP NAME    NO NB_ARGS FCT_PTR     OCP   ARG(S)_TYPE
	{"no_op",	0,	0,	NULL,			0,	{0}},
	{"live",	1,	1,	&live_instr,	0,	{T_DIR}},
	{"ld",		2,	2,	&load_instr,	1,	{T_DIR|T_IND, T_REG}},
	{"st",		3,	2,	&store_instr,	1,	{T_REG, T_IND|T_REG}}
};

#endif
