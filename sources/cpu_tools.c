/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:21:21 by upopee            #+#    #+#             */
/*   Updated: 2018/03/05 12:17:10 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

void		init_cpu(t_vcpu *cpu, uint8_t *memory)
{
	ft_bzero(cpu, sizeof(*cpu));
	cpu->memory = memory;
}

void 		load_process(t_vcpu *cpu, uint8_t *p_regs, uint64_t p_pc)
{
	cpu->registers = p_regs;
	cpu->pc = p_pc;
}

/*
** -- JUMP PC
**    > Get the PC address of a jump_pos value
*/

uint64_t	jump_to(uint64_t pc, uint64_t jump_pos)
{
	uint64_t	cumul;

	cumul = pc + jump_pos;
	while (cumul >= MEM_SIZE)
		cumul -= MEM_SIZE;
	return (cumul);
}

/*
** -- SECURE FECTH
**    > Handle the circular memory difficulty automatically
**    > BIG_ENDIAN >> LITTLE_ENDIAN
*/

void		secure_fetch(uint64_t *pc, uint8_t *memory, uint8_t *dst, size_t sz)
{
	uint32_t	buff;

	if (*pc + sz < MEM_SIZE)
	{
		buff = 0;
		ft_memcpy(&buff, memory + *pc, sz);
		*dst = SWAP_UINT32(buff);
		*pc += sz;
	}
	else
	{
		while (sz--)
		{
			dst[sz] = *(memory + *pc);
			++(*pc);
			if (*pc == MEM_SIZE)
				*pc = 0;
		}
	}
}
