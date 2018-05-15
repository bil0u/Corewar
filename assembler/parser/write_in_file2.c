/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_file2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:40:39 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 20:42:12 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	write_register(char *buf, int *index, t_list *lst, int arg)
{
	uint16_t	inttmp;

	inttmp = LST_I->params[arg].value.i;
	ft_memcpy(buf + *index, &inttmp, 1);
	(*index)++;
}

void	write_direct_label(char *buf, int *index, t_list *lst, int arg)
{
	uint16_t	inttmp;
	uint32_t	longtmp;

	if (LST_I->infos->short_directs == 1)
	{
		inttmp = SWAP_UINT16((uint16_t)LST_I->params[arg].value.i);
		ft_memcpy(buf + *index, &inttmp, 2);
	}
	else
	{
		longtmp = SWAP_UINT32((uint32_t)LST_I->params[arg].value.i);
		ft_memcpy(buf + *index, &longtmp, 4);
	}
	*index += LST_I->infos->short_directs == 1 ? 2 : 4;
}

void	write_indirect_label(char *buf, int *index, t_list *lst, int arg)
{
	uint16_t	inttmp;

	inttmp = SWAP_UINT16((uint16_t)LST_I->params[arg].value.i);
	ft_memcpy(buf + *index, &inttmp, 2);
	*index += 2;
}

int		find_address_label(char *str, t_infos *infos)
{
	t_list	*lst;

	lst = LABELS;
	while (lst)
	{
		if (!ft_strcmp(str, LST_L->name))
		{
			return (LST_L->address);
		}
		lst = lst->next;
	}
	return (unknown_label_error(infos, str));
}

char	get_codage(t_instruction *instruction)
{
	char	ocp;
	int		arg;
	int		shift;

	ocp = 0;
	shift = 6;
	arg = -1;
	while (++arg < instruction->infos->nb_args)
	{
		if (instruction->params[arg].type & 0x1)
			ocp = ocp | (ARG_REG << shift);
		if (instruction->params[arg].type & 0x2)
			ocp = ocp | (ARG_DIR << shift);
		if (instruction->params[arg].type & 0x4)
			ocp = ocp | (ARG_IND << shift);
		shift -= 2;
	}
	return (ocp);
}
