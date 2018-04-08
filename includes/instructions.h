/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/04/08 14:07:52 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define NB_INSTRUCTIONS	17

int		live_instr(t_vcpu *cpu, t_vcpudata *dat);
int		ld_instr(t_vcpu *cpu, t_vcpudata *dat);
int		st_instr(t_vcpu *cpu, t_vcpudata *dat);
int		add_instr(t_vcpu *cpu, t_vcpudata *dat);
int		sub_instr(t_vcpu *cpu, t_vcpudata *dat);
int		and_instr(t_vcpu *cpu, t_vcpudata *dat);
int		or_instr(t_vcpu *cpu, t_vcpudata *dat);
int		xor_instr(t_vcpu *cpu, t_vcpudata *dat);
int		zjmp_instr(t_vcpu *cpu, t_vcpudata *dat);
int		ldi_instr(t_vcpu *cpu, t_vcpudata *dat);
int		sti_instr(t_vcpu *cpu, t_vcpudata *dat);
int		fork_instr(t_vcpu *cpu, t_vcpudata *dat);
int		lld_instr(t_vcpu *cpu, t_vcpudata *dat);
int		lldi_instr(t_vcpu *cpu, t_vcpudata *dat);
int		lfork_instr(t_vcpu *cpu, t_vcpudata *dat);
int		aff_instr(t_vcpu *cpu, t_vcpudata *dat);

t_op    g_op_set[NB_INSTRUCTIONS] =
{
//	OP NAME     FCT_PTR     OP_NO ARGS OCP INDEX ARG(S)_TYPE
	{"no_op",	NULL,			0,	0,	0,	0,	{0}},
	{"live",	&live_instr,	1,	1,	0,	0,	{T_DIR}},
	{"ld",		&ld_instr,		2,	2,	1,	0,	{T_DIR|T_IND, T_REG}},
	{"st",		&st_instr,		3,	2,	1,	0,	{T_REG, T_IND|T_REG}},
	{"add",		&add_instr,		4,	3,	1,	0,	{T_REG, T_REG, T_REG}},
	{"sub",		&sub_instr,		5,	3,	1,	0,	{T_REG, T_REG, T_REG}},
	{"and",		&and_instr,		6,	3,	1,	0,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"or",		&or_instr,		7,	3,	1,	0,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"xor",		&xor_instr,		8,	3,	1,	0,	{T_REG|T_DIR|T_IND, T_REG|T_DIR|T_IND, T_REG}},
	{"zjmp",	&zjmp_instr,	9,	1,	0,	1,	{T_DIR}},
	{"ldi",		&ldi_instr,		10,	3,	1,	1,	{T_REG|T_DIR|T_IND, T_DIR|T_REG, T_REG}},
	{"sti",		&sti_instr,		11,	3,	1,	1,	{T_REG, T_REG|T_DIR|T_IND, T_DIR|T_REG}},
	{"fork",	&fork_instr,	12,	1,	0,	1,	{T_DIR}},
	{"lld",		&lld_instr,		13,	2,	1,	0,	{T_DIR|T_IND, T_REG}},
	{"lldi",	&lldi_instr,	14,	3,	1,	1,	{T_REG|T_DIR|T_IND, T_DIR|T_REG, T_REG}},
	{"lfork",	&lfork_instr,	15,	1,	0,	1,	{T_DIR}},
	{"aff",		&aff_instr,		16,	1,	1,	0,	{T_REG}}
};

#endif
