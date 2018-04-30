/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:22:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/30 14:32:11 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VCPU_H
# define VCPU_H

/*
** -- CPU CORE --
*/

void		exec_or_wait(t_vcpu *c, t_process *p, t_player *pl, t_gamectrl *g);

/*
** -- CPU TOOLS --
*/

uint16_t	jump_to(uint16_t pc, int16_t jump_len);
uint8_t		get_argsize(uint8_t arg_type);
void		decode_arg(uint8_t *mem, t_process *p, uint8_t type, uint32_t *buf);
void		secure_fetch(uint8_t *mem, uint16_t pc, uint32_t *dst, size_t sz);
void		secure_store(t_vcpu *cpu, uint8_t p_no, uint32_t src, size_t sz);

#endif
