/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:22:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/15 18:00:45 by upopee           ###   ########.fr       */
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
void		secure_fetch(uint64_t *pc, uint8_t *memory, t_arg *dst, size_t s);

/*
**	-------- CPU _DEBUG  ---------
*/

void	print_memory(t_vcpu *cpu);
void	print_registers(t_vcpu *cpu);

#endif
