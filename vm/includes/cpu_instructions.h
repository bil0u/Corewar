/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/05/16 00:49:41 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_INSTRUCTIONS_H
# define CPU_INSTRUCTIONS_H

/*
**	-- SUPPORTED VCPU INSTRUCTIONS --
*/

int		live_instr(t_vcpu *cpu, t_process *p, t_player *pl, t_gamectrl *g);
int		ld_instr(t_vcpu *cpu, t_process *p);
int		st_instr(t_vcpu *cpu, t_process *p);
int		add_instr(t_vcpu *cpu, t_process *p);
int		sub_instr(t_vcpu *cpu, t_process *p);
int		and_instr(t_vcpu *cpu, t_process *p);
int		or_instr(t_vcpu *cpu, t_process *p);
int		xor_instr(t_vcpu *cpu, t_process *p);
int		zjmp_instr(t_vcpu *cpu, t_process *p);
int		ldi_instr(t_vcpu *cpu, t_process *p);
int		sti_instr(t_vcpu *cpu, t_process *p);
int		fork_instr(t_vcpu *cpu, t_process *p, t_player *pl);
int		lld_instr(t_vcpu *cpu, t_process *p);
int		lldi_instr(t_vcpu *cpu, t_process *p);
int		lfork_instr(t_vcpu *cpu, t_process *p, t_player *pl);
int		aff_instr(t_vcpu *cpu, t_process *p, t_player *pl);

/*
** > OP NAME | FCT_PTR | COST IN CYCLES
**     OP_NO | NB_ARGS | HAS OCP | SHORT_DIRECTS | ACCEPTED ARG(S)_TYPE
*/

t_op	g_op_set[NB_OPS] =
{
	{"live", &live_instr, 10,
		1, 1, 0, 0, {T_DIR}},
	{"ld", &ld_instr, 5,
		2, 2, 1, 0, {T_DIR | T_IND, T_REG}},
	{"st", &st_instr, 5,
		3, 2, 1, 0, {T_REG, T_IND | T_REG}},
	{"add", &add_instr, 10,
		4, 3, 1, 0, {T_REG, T_REG, T_REG}},
	{"sub", &sub_instr, 10,
		5, 3, 1, 0, {T_REG, T_REG, T_REG}},
	{"and", &and_instr, 6,
		6, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"or", &or_instr, 6,
		7, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"xor", &xor_instr, 6,
		8, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"zjmp", &zjmp_instr, 20,
		9, 1, 0, 1, {T_DIR}},
	{"ldi", &ldi_instr, 25,
		10, 3, 1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"sti", &sti_instr, 25,
		11, 3, 1, 1, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	{"fork", &fork_instr, 800,
		12, 1, 0, 1, {T_DIR}},
	{"lld", &lld_instr, 10,
		13, 2, 1, 0, {T_DIR | T_IND, T_REG}},
	{"lldi", &lldi_instr, 50,
		14, 3, 1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"lfork", &lfork_instr, 1000,
		15, 1, 0, 1, {T_DIR}},
	{"aff", &aff_instr, 2,
		16, 1, 1, 0, {T_REG}}
};

#endif
