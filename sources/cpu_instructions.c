/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:49:45 by upopee            #+#    #+#             */
/*   Updated: 2018/03/15 18:46:31 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"

void	live_instr(t_vcpu *cpu)
{
	int			fd;

	fd = (get_logwin("ins"))->fd;

	secure_fetch(&cpu->pc, cpu->memory, cpu->op_args, ARG_DIRSZ);
	ft_dprintf(fd, "Player %d is alive !\n", cpu->op_args[0]);
}

void	load_instr(t_vcpu *cpu)
{
	(void)cpu;
}
