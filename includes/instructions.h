/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:29:37 by upopee            #+#    #+#             */
/*   Updated: 2018/03/02 16:50:22 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
**	-------- INSTRUCTIONS ALLOWED ---------
*/

# define INSTR_NUMBER	3

void	no_instr(uint8_t *memory, uint8_t *regs, uint8_t *carry, t_arg *args);
void	live_instr(uint8_t *memory, uint8_t *regs, uint8_t *carry, t_arg *args);
void	load_instr(uint8_t *memory, uint8_t *regs, uint8_t *carry, t_arg *args);

t_op    g_op_set[INSTR_NUMBER] =
{
	{"no_op",	0,	0,	&no_instr},
	{"live",	1,	1,	&live_instr},
	{"ld",		2,	2,	&load_instr}
};

#endif