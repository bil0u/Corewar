/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/03/05 10:16:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define NB_INSTRUCTIONS	3

void	live_instr(uint8_t *memory, uint8_t *regs, uint8_t *carry, t_arg *args);
void	load_instr(uint8_t *memory, uint8_t *regs, uint8_t *carry, t_arg *args);

t_op    g_op_set[NB_INSTRUCTIONS] =
{
	{"no_op",	0,	0,	NULL,			{0}},
	{"live",	1,	1,	&live_instr,	{T_DIR}},
	{"ld",		2,	2,	&load_instr,	{T_DIR|T_IND, T_REG}}
};

#endif
