/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:21:21 by upopee            #+#    #+#             */
/*   Updated: 2018/03/22 17:05:38 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"

void		init_cpu(t_vcpu *cpu, uint8_t *memory)
{
	ft_bzero(cpu, sizeof(*cpu));
	cpu->memory = memory;
}

void 		load_process(t_vcpu *cpu, uint32_t *p_regs, uint32_t p_pc)
{
	cpu->registers = p_regs;
	cpu->pc = p_pc;
}

/*
** -- JUMP TO
**    > Return the PC address of a jump_pos value
*/

uint32_t	jump_to(uint32_t pc, int jump_len)
{
	int		tmp;

	tmp = pc + jump_len;
	while (tmp < 0)
		tmp += MEM_SIZE;
	while (tmp >= MEM_SIZE)
		tmp -= MEM_SIZE;
	return ((uint32_t)tmp);
}

/*
** -- GET ARG SIZE
**    > Return the associated size for a given arg type
*/

uint8_t		get_argsize(uint8_t arg_type)
{
	if (arg_type == ARG_REG)
		return (ARG_REGSZ);
	else if (arg_type == ARG_IND)
		return (ARG_INDSZ);
	else if (arg_type == ARG_DIR)
		return (ARG_DIRSZ);
	else
		return (0);
}

/*
** -- SECURE FETCH DATA IN MEMORY
**    > Handle the circular memory
**    > BIG_ENDIAN >> LITTLE_ENDIAN
*/

void		secure_fetch(uint32_t pc, uint8_t *memory, uint32_t *dst, size_t sz)
{
	uint8_t		*tmp;

	*dst = 0;
	tmp = (uint8_t *)dst;
	if (pc + sz < MEM_SIZE)
	{
		while (sz--)
		{
			*(tmp + sz) = *(memory + pc);
			++pc;
		}
	}
	else
	{
		while (sz--)
		{
			*(tmp + sz) = *(memory + pc);
			pc = (pc + 1 == MEM_SIZE) ? 0 : pc + 1;
		}
	}
}

/*
** -- SECURE STORE DATA IN MEMORY
**    > Handle the circular memory
**    > LITTLE_ENDIAN >> BIG_ENDIAN
*/

void		secure_store(uint32_t pc, uint8_t *memory, uint32_t src, size_t sz)
{
	uint8_t		*tmp;

	tmp = (uint8_t *)(&src);
	if (pc + sz < MEM_SIZE)
	{
		while (sz--)
		{
			*(memory + pc) = *(tmp + sz);
			++pc;
		}
	}
	else
	{
		while (sz--)
		{
			*(memory + pc) = *(tmp + sz);
			pc = (pc + 1 == MEM_SIZE) ? 0 : pc + 1;
		}
	}
}
