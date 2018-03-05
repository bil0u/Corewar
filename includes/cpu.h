/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:22:49 by upopee            #+#    #+#             */
/*   Updated: 2018/03/05 04:45:42 by upopee           ###   ########.fr       */
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

void	init_cpu(t_vcpu *cpu, uint8_t *memory);
void 	load_process(t_vcpu *cpu, uint8_t *process_regs, uint64_t process_pc);

/*
**	-------- CPU _DEBUG  ---------
*/

void	print_memory(char *name, uint8_t *s, uint64_t len, uint64_t pc);
void	print_cpu(t_vcpu *cpu);

#endif
