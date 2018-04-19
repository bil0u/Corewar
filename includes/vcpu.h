/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vcpu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:22:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/19 17:41:18 by upopee           ###   ########.fr       */
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

uint32_t	jump_to(uint32_t pc, int16_t jump_len);
uint8_t		get_argsize(uint8_t arg_type);
int			decode_arg(t_vcpu *c, t_process *p, uint8_t at, uint32_t *ab);
void		secure_fetch(uint32_t pc, uint8_t *mem, uint32_t *dst, size_t sz);
void		secure_store(uint32_t pc, uint8_t *mem, uint32_t src, size_t sz);

#endif
