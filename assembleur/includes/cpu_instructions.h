/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/05/03 21:01:00 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_INSTRUCTIONS_H
# define CPU_INSTRUCTIONS_H

/*
** > OP NAME    FCT_PTR    TIME
**                              NO  NBA OCP SHORT_DIRECTS ARG(S)_TYPE
*/

t_op	g_op_set[NB_OPS] =
{
	{"live", NULL, 10,
		1, 1, 0, 0, {T_DIR}},
	{"ld", NULL, 5,
		2, 2, 1, 0, {T_DIR | T_IND, T_REG}},
	{"st", NULL, 5,
		3, 2, 1, 0, {T_REG, T_IND | T_REG}},
	{"add", NULL, 10,
		4, 3, 1, 0, {T_REG, T_REG, T_REG}},
	{"sub", NULL, 10,
		5, 3, 1, 0, {T_REG, T_REG, T_REG}},
	{"and", NULL, 6,
		6, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"or", NULL, 6,
		7, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"xor", NULL, 6,
		8, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"zjmp", NULL, 20,
		9, 1, 0, 1, {T_DIR}},
	{"ldi", NULL, 25,
		10, 3, 1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"sti", NULL, 25,
		11, 3, 1, 1, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	{"fork", NULL, 800,
		12, 1, 0, 1, {T_DIR}},
	{"lld", NULL, 10,
		13, 2, 1, 0, {T_DIR | T_IND, T_REG}},
	{"lldi", NULL, 50,
		14, 3, 1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"lfork", NULL, 1000,
		15, 1, 0, 1, {T_DIR}},
	{"aff", NULL, 2,
		16, 1, 1, 0, {T_REG}}
};

#endif
