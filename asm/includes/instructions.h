/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/05/02 19:45:41 by glictevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

# define NB_INSTRUCTIONS	17

/*
**	OP NAME    OP_NO ARGS OCP INDEX ARG(S)_TYPE
*/
t_op	g_op_set[NB_INSTRUCTIONS] =
{
	{"no_op", 0, 0, 0, 0, {0}},
	{"live", 1, 1, 0, 0, {T_DIR}},
	{"ld", 2, 2, 1, 0, {T_DIR | T_IND, T_REG}},
	{"st", 3, 2, 1, 0, {T_REG, T_IND | T_REG}},
	{"add", 4, 3, 1, 0, {T_REG, T_REG, T_REG}},
	{"sub", 5, 3, 1, 0, {T_REG, T_REG, T_REG}},
	{"and", 6, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"or", 7, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"xor", 8, 3, 1, 0, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}},
	{"zjmp", 9, 1, 0, 1, {T_DIR}},
	{"ldi", 10, 3, 1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"sti", 11, 3, 1, 1, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	{"fork", 12, 1, 0, 1, {T_DIR}},
	{"lld", 13, 2, 1, 0, {T_DIR | T_IND, T_REG}},
	{"lldi", 14, 3, 1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	{"lfork", 15, 1, 0, 1, {T_DIR}},
	{"aff", 16, 1, 1, 0, {T_REG}}
};

#endif
