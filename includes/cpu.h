/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:22:49 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 09:55:36 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H

/*
** -- CPU CORE --
*/

void		exec_or_wait(t_vcpu *cpu, t_process *process,
							t_player *player, t_gamectrl *game);

/*
** -- CPU TOOLS --
*/

uint32_t	jump_to(uint32_t pc, int jump_pos);
uint8_t		get_argsize(uint8_t arg_type);
int			decode_arg(t_vcpu *cpu, t_process *process,
							uint8_t arg_type, uint32_t *arg_buff);
void		secure_fetch(uint32_t pc, uint8_t *mem, uint32_t *dst, size_t sz);
void		secure_store(uint32_t pc, uint8_t *mem, uint32_t src, size_t sz);

#endif
