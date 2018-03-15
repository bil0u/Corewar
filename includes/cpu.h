/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:22:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/15 14:14:42 by upopee           ###   ########.fr       */
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
void 		load_process(t_vcpu *cpu, uint8_t *process_regs, uint64_t process_pc);
uint64_t	jump_to(uint64_t pc, uint64_t jump_pos);
void		secure_fetch(uint64_t *pc, uint8_t *memory, uint8_t *dst, size_t s);

/*
**	-------- CPU _DEBUG  ---------
*/

void	print_memory(uint8_t *mem, uint32_t len, uint64_t pc, int fd);
void	print_cpu(t_vcpu *cpu);

#endif
