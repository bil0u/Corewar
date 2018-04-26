/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:21:21 by upopee            #+#    #+#             */
/*   Updated: 2018/04/26 19:03:59 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"

/*
** -- JUMP TO
**    > Return the PC address of a jump_pos value
*/

uint16_t	jump_to(uint16_t pc, int16_t index)
{
	int16_t		index_tmp;

	index_tmp = pc + index;
	while (index_tmp < 0)
		index_tmp += MEM_SIZE;
	index_tmp &= (MEM_SIZE - 1);
	return ((uint16_t)index_tmp);
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
** -- INTERPRET ARGS VALUE
*/

void		decode_arg(uint8_t *mem, t_process *p, uint8_t type, uint32_t *buff)
{
	int16_t		ind;

	if (type == ARG_REG)
		*buff = p->registers[*buff - 1];
	else if (type == ARG_IND)
	{
		ind = jump_to(p->pc, TOI16(*buff));
		*buff = 0;
		secure_fetch(ind, mem, buff, REG_SIZE);
	}
	else if (type == ARG_DIR && p->next_op->ind_address)
		*buff = TOU32(TOI32(TOI16(*buff)));
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
