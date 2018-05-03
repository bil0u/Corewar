/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:36:14 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 22:52:16 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_direct_label(t_lexer *lexer)
{
	int		tmp;

	if (*(LINE + INDEX) == DIRECT_CHAR)
	{
		if (*(LINE + INDEX + 1) == LABEL_CHAR)
			return (is_direct_label_text(lexer));
		tmp = ft_atoi(LINE + INDEX + 1);
		INDEX++;
		TOKEN->value.i = tmp;
		tmp = INDEX;
		if (*(LINE + INDEX) == '-')
			INDEX++;
		while (*(LINE + INDEX) && *(LINE + INDEX) >= '0' &&
			*(LINE + INDEX) <= '9')
			INDEX++;
		if (INDEX == tmp)
		{
			INDEX = tmp;
			return (0);
		}
		TOKEN->valuetype = 'i';
		TOKEN->type = DIRECT_LABEL;
		return (1);
	}
	return (0);
}

int		is_direct_label_text(t_lexer *lexer)
{
	INDEX += 2;
	if (!is_text(lexer))
	{
		INDEX -= 2;
		return (0);
	}
	TOKEN->type = DIRECT_LABEL;
	TOKEN->valuetype = 's';
	return (1);
}

int		is_indirect_label(t_lexer *lexer)
{
	if (*(LINE + INDEX) == LABEL_CHAR)
	{
		INDEX++;
		if (!is_text(lexer))
		{
			INDEX--;
			return (0);
		}
		TOKEN->type = INDIRECT_LABEL;
		return (1);
	}
	return (is_indirect_label_number(lexer));
}

int		is_indirect_label_number(t_lexer *lexer)
{
	int		tmp;

	tmp = ft_atoi(LINE + INDEX);
	TOKEN->value.i = tmp;
	tmp = INDEX;
	if (*(LINE + INDEX) == '-')
		INDEX++;
	while (*(LINE + INDEX) && *(LINE + INDEX) >= '0' && *(LINE + INDEX) <= '9')
		INDEX++;
	if (*(LINE + INDEX) == LABEL_CHAR || INDEX == tmp)
	{
		INDEX = tmp;
		return (0);
	}
	TOKEN->valuetype = 'i';
	TOKEN->type = INDIRECT_LABEL;
	return (1);
}
