/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:21:21 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 14:45:48 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_endline(t_lexer *lexer)
{
	if (*(LINE + INDEX) == '\0' || *(LINE + INDEX) == COMMENT_CHAR)
	{
		TOKEN->type = ENDLINE;
		return (1);
	}
	return (0);
}

int		is_separator(t_lexer *lexer)
{
	if (*(LINE + INDEX) == SEPARATOR_CHAR)
	{
		TOKEN->type = SEPARATOR;
		INDEX++;
		return (1);
	}
	return (0);
}

int		is_name(t_lexer *lexer)
{
	int		tmp;
	int		str_len;
	char	*tmpc;

	if (ft_strncmp(LINE + INDEX, NAME_CMD_STRING,
		(tmp = ft_strlen(NAME_CMD_STRING))) == 0)
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
			TOKEN->type = NAME;
			INDEX += 2 + str_len;
			return (1);
		}
	}
	return (0);
}
