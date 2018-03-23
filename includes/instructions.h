/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/03/23 17:23:58 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define NB_INSTRUCTIONS	11

int		live_instr(t_vcpu *cpu);
int		load_instr(t_vcpu *cpu);
int		store_instr(t_vcpu *cpu);
int		add_instr(t_vcpu *cpu);
int		sub_instr(t_vcpu *cpu);
int		and_instr(t_vcpu *cpu);
int		or_instr(t_vcpu *cpu);
int		xor_instr(t_vcpu *cpu);
int		zjmp_instr(t_vcpu *cpu);
int		ldi_instr(t_vcpu *cpu);

t_op    g_op_set[NB_INSTRUCTIONS] =
{
//	OP NAME     FCT_PTR     OP_NO ARGS OCP INDEX ARG(S)_TYPE
	{"no_op",	NULL,			0,	0,	0,	0,	{0}},
	{"live",	&live_instr,	1,	1,	0,	0,	{T_DIR}},
	{"ld",		&load_instr,	2,	2,	1,	0,	{T_DIR|T_IND, T_REG}},
	{"st",		&store_instr,	3,	2,	1,	0,	{T_REG, T_IND|T_REG}},
	{"add",		&add_instr,		4,	3,	1,	0,	{T_REG, T_REG, T_REG}},
	{"sub",		&sub_instr,		5,	3,	1,	0,	{T_REG, T_REG, T_REG}},
	{"and",		&and_instr,		6,	3,	1,	0,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"or",		&or_instr,		7,	3,	1,	0,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"xor",		&xor_instr,		8,	3,	1,	0,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"zjmp",	&zjmp_instr,	9,	1,	0,	1,	{T_DIR}},
	{"ldi",		&ldi_instr,		10,	3,	1,	1,	{T_REG|T_DIR|T_IND, T_DIR|T_REG, T_REG}}
};

#endif
