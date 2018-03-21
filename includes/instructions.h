/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/03/21 00:25:45 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define NB_INSTRUCTIONS	10

int		live_instr(t_vcpu *cpu);
int		load_instr(t_vcpu *cpu);
int		store_instr(t_vcpu *cpu);
int		add_instr(t_vcpu *cpu);
int		sub_instr(t_vcpu *cpu);
int		and_instr(t_vcpu *cpu);
int		or_instr(t_vcpu *cpu);
int		xor_instr(t_vcpu *cpu);
int		zjmp_instr(t_vcpu *cpu);

t_op    g_op_set[NB_INSTRUCTIONS] =
{
//	OP NAME    NO NB_ARGS FCT_PTR     OCP   ARG(S)_TYPE
	{"no_op",	0,	0,	NULL,			0,	{0}},
	{"live",	1,	1,	&live_instr,	0,	{T_DIR}},
	{"ld",		2,	2,	&load_instr,	1,	{T_DIR|T_IND, T_REG}},
	{"st",		3,	2,	&store_instr,	1,	{T_REG, T_IND|T_REG}},
	{"add",		4,	3,	&add_instr,		1,	{T_REG, T_REG, T_REG}},
	{"sub",		5,	3,	&sub_instr,		1,	{T_REG, T_REG, T_REG}},
	{"and",		6,	3,	&and_instr,		1,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"or",		7,	3,	&or_instr,		1,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"xor",		8,	3,	&xor_instr,		1,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"zjmp",	9,	1,	&zjmp_instr,	0,	{T_DIR}}
};

#endif
