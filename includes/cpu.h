/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:22:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/17 19:32:38 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H

/*
** --------- CPU CORE ------------
*/

/*
** --------- CPU TOOLS ------------
*/

void		init_cpu(t_vcpu *cpu, uint8_t *memory);
void 		load_process(t_vcpu *cpu, uint32_t *p_regs, uint32_t p_pc);
uint32_t	jump_to(uint32_t pc, int jump_pos);
void		secure_fetch(uint32_t pc, uint8_t *mem, uint32_t *dst, size_t sz);
void		secure_store(uint32_t pc, uint8_t *mem, uint32_t src, size_t sz);

/*
**	-------- CPU _DEBUG  ---------
*/

void		print_memory(t_vcpu *cpu);
void		print_registers(t_vcpu *cpu);

#endif
