/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 13:53:53 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 20:38:15 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		parse_parameters(t_lexer *lexer, t_infos *infos, t_list *lst)
{
	int		arg;
	int		need_separator;

	arg = 0;
	need_separator = 0;
	while (arg < LST_I->infos->nb_args)
	{
		if (need_separator == 1)
		{
			if (eat(lexer, SEPARATOR) == 0)
				return (0);
			need_separator = 0;
			continue;
		}
		if (parse_reg(lexer, lst, arg) || parse_dir_label(lexer, lst, arg) ||
			parse_indir_label(lexer, lst, arg))
		{
			arg++;
			need_separator = 1;
			continue;
		}
		return (wrong_argument_error(lexer, LST_I, arg));
	}
	ADDR_INDEX += LST_I->size;
	return (1);
}

int		parse_reg(t_lexer *lexer, t_list *lst, int arg)
{
	if (LST_I->infos->valid_types[arg] & 0x1)
	{
		if (check(lexer, REGISTER))
		{
			LST_I->size += 1;
			LST_I->params[arg].type = T_REG;
			LST_I->params[arg].value = TOKEN->value;
			LST_I->params[arg].valuetype = TOKEN->valuetype;
			if (!eat(lexer, REGISTER))
				return (0);
			return (1);
		}
	}
	return (0);
}

int		parse_dir_label(t_lexer *lexer, t_list *lst, int arg)
{
	if (LST_I->infos->valid_types[arg] & 0x2)
	{
		if (check(lexer, DIRECT_LABEL))
		{
			if (LST_I->infos->short_directs == 1)
				LST_I->size += 2;
			else
				LST_I->size += 4;
			LST_I->params[arg].type = T_DIR;
			LST_I->params[arg].value = TOKEN->value;
			LST_I->params[arg].valuetype = TOKEN->valuetype;
			if (!eat(lexer, DIRECT_LABEL))
				return (0);
			return (1);
		}
	}
	return (0);
}

int		parse_indir_label(t_lexer *lexer, t_list *lst, int arg)
{
	if (LST_I->infos->valid_types[arg] & 0x4)
	{
		if (check(lexer, INDIRECT_LABEL))
		{
			LST_I->size += 2;
			LST_I->params[arg].type = T_IND;
			LST_I->params[arg].value = TOKEN->value;
			LST_I->params[arg].valuetype = TOKEN->valuetype;
			if (!eat(lexer, INDIRECT_LABEL))
				return (0);
			return (1);
		}
	}
	return (0);
}
