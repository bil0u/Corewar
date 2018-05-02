/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:21:21 by upopee            #+#    #+#             */
/*   Updated: 2018/05/02 04:17:11 by upopee           ###   ########.fr       */
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

void		secure_fetch(uint8_t *memory, uint16_t pc, uint32_t *dst, size_t sz)
{
	uint8_t		*tmp;

	*dst = 0;
	tmp = (uint8_t *)dst;
	if (pc + sz < MEM_SIZE)
		while (sz--)
		{
			*(tmp + sz) = *(memory + pc);
			++pc;
		}
	else
		while (sz--)
		{
			*(tmp + sz) = *(memory + pc);
			pc = (pc + 1 == MEM_SIZE) ? 0 : pc + 1;
		}
}

/*
** -- SECURE STORE DATA IN MEMORY
**    > Handle the circular memory
**    > LITTLE_ENDIAN >> BIG_ENDIAN
*/

void		secure_store(t_vcpu *cpu, uint8_t p_no, uint32_t src, size_t sz)
{
	uint16_t	*flags;
	uint8_t		*mem;
	uint8_t		*tmp;
	uint16_t	pc;

	tmp = (uint8_t *)(&src);
	pc = cpu->pc_copy;
	mem = cpu->memory;
	flags = cpu->m_flags;
	if (pc + sz < MEM_SIZE)
		while (sz--)
		{
			*(mem + pc) = *(tmp + sz);
			*(flags + pc) = CWCF_PNO(p_no) | CWCF_RWRITE;
			++pc;
		}
	else
		while (sz--)
		{
			*(mem + pc) = *(tmp + sz);
			*(flags + pc) = CWCF_PNO(p_no) | CWCF_RWRITE;
			pc = (pc + 1 == MEM_SIZE) ? 0 : pc + 1;
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
		if (p->next_op->op_number < 13)
			ind = jump_to(p->pc, TOI16(*buff) % IDX_MOD);
		else
			ind = jump_to(p->pc, TOI16(*buff));
		secure_fetch(mem, ind, buff, REG_SIZE);
	}
	else if (type == ARG_DIR && p->next_op->short_directs)
		*buff = TOU32(TOI32(TOI16(*buff)));
}
