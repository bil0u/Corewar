/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:36:21 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 14:45:51 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_comment(t_lexer *lexer)
{
	int		tmp;
	int		str_len;
	char	*tmpc;

	if (ft_strncmp(LINE + INDEX, COMMENT_CMD_STRING,
		(tmp = ft_strlen(COMMENT_CMD_STRING))) == 0)
	{
		INDEX += tmp;
		pass_spaces(lexer);
		if (*(LINE + INDEX) == '"')
		{
			if ((tmpc = ft_strchr(LINE + INDEX + 1, '"')) == NULL)
				return (missing_closing_quote_error(lexer));
			str_len = ft_strlen(LINE) - ft_strlen(tmpc) - (INDEX + 1);
			TOKEN->value.s = ft_strsub(LINE, INDEX + 1, str_len);
			TOKEN->valuetype = 's';
			if (TOKEN->value.s == NULL)
				return (0);
			TOKEN->type = COMMENT;
			INDEX += 2 + str_len;
			return (1);
		}
	}
	return (0);
}

int		is_register(t_lexer *lexer)
{
	int		tmp;

	if (*(LINE + INDEX) == 'r')
	{
		tmp = ft_atoi(LINE + INDEX + 1);
		if (tmp < 0 || tmp > REG_NUMBER)
		{
			TOKEN->type = ERROR;
			return (0);
		}
		else if (tmp == 0 && *(LINE + INDEX + 1) != '0')
			return (0);
		TOKEN->value.i = tmp;
		TOKEN->type = REGISTER;
		TOKEN->valuetype = 'i';
		INDEX += 1 + ft_nbrlen_base(tmp, 10);
		return (1);
	}
	return (0);
}

int		is_text(t_lexer *lexer)
{
	int		start;

	start = INDEX;
	while (ft_strchr(LABEL_CHARS, *(LINE + INDEX)) !=
		NULL && *(LINE + INDEX) != '\0')
		INDEX++;
	if (start == INDEX)
		return (0);
	TOKEN->value.s = ft_strsub(LINE, start, INDEX - start);
	if (TOKEN->value.s == NULL)
		return (0);
	TOKEN->type = TEXT;
	TOKEN->valuetype = 's';
	return (1);
}

int		is_label(t_lexer *lexer)
{
	int		tmp;

	tmp = is_text(lexer);
	if (tmp == 1 && *(LINE + INDEX) == LABEL_CHAR)
	{
		TOKEN->type = LABEL;
		TOKEN->valuetype = 's';
		INDEX++;
		return (1);
	}
	else if (tmp == 1)
		return (1);
	return (0);
}
