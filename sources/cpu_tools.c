/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:21:21 by upopee            #+#    #+#             */
/*   Updated: 2018/03/16 03:17:06 by upopee           ###   ########.fr       */
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
** -- JUMP TO
**    > Return the PC address of a jump_pos value
*/

uint64_t	jump_to(uint64_t pc, int jump_len)
{
	int		tmp;

	tmp = pc + jump_len;
	while (tmp < 0)
		tmp += MEM_SIZE;
	while (tmp >= MEM_SIZE)
		tmp -= MEM_SIZE;
	return (tmp);
}

/*
** -- SECURE FETCH ARG
**    > Handle the circular memory
**    > BIG_ENDIAN >> LITTLE_ENDIAN
*/

void		secure_fetch(uint64_t *pc, uint8_t *memory, t_arg *dst, size_t sz)
{
	uint32_t	buff;
	uint8_t		*tmp;

	if (*pc + sz < MEM_SIZE)
	{
		buff = 0;
		ft_memcpy(&buff, memory + *pc, sz);
		*dst = SWAP_UINT32(buff);
		*pc += sz;
	}
	else
	{
		tmp = (uint8_t *)dst;
		while (sz--)
		{
			tmp[sz] = *(memory + *pc);
			++(*pc);
			if (*pc == MEM_SIZE)
				*pc = 0;
		}
	}
}
