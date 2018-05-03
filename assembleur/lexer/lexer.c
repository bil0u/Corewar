/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 11:39:48 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 21:50:10 by glictevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		initialize_lexer(t_lexer *lexer, int fd, char *filename)
{
	FILENAME = filename;
	FD = fd;
	LINE_NB = 0;
	if ((TOKEN = (t_token *)ft_memalloc(sizeof(t_token))) == NULL)
		return (malloc_fail_error(lexer));
	if (!call_gnl(lexer, 0))
		return (0);
	return (find_next_token(lexer));
}

int		find_next_token(t_lexer *lexer)
{
	if (TOKEN->type == ENDLINE)
		if (!call_gnl(lexer, 0))
			return (0);
	if (TOKEN->type == END)
		return (1);
	pass_spaces(lexer);
	PREV_INDEX = INDEX + 1;
	if (is_endline(lexer)
	|| is_separator(lexer)
	|| is_name(lexer)
	|| is_comment(lexer)
	|| is_direct_label(lexer)
	|| is_indirect_label(lexer)
	|| is_register(lexer)
	|| is_label(lexer))
		return (1);
	TOKEN->type = ERROR;
	return (1);
}

int		eat(t_lexer *lexer, t_token_type token)
{
	if (TOKEN->type == token)
	{
		TOKEN->valuetype = ' ';
		TOKEN->value.s = NULL;
		find_next_token(lexer);
	}
	else
	{
		return (eat_error(lexer, token));
	}
	return (1);
}

int		check(t_lexer *lexer, t_token_type token)
{
	if (TOKEN->type == token)
		return (1);
	return (0);
}

int		call_gnl(t_lexer *lexer, int option)
{
	int		ret;

	if (LINE_NB >= 1)
		free(LINE);
	LINE = NULL;
	if (option == 1)
	{
		if ((ret = get_next_line_opt(FD, &LINE, 1)) == -1)
			return (malloc_fail_error(lexer));
		return (1);
	}
	if ((ret = get_next_line_opt(FD, &LINE, 0)) == -1)
		return (malloc_fail_error(lexer));
	if (ret == 0)
	{
		TOKEN->type = END;
		return (1);
	}
	LINE_NB++;
	TOKEN->type = ERROR;
	INDEX = 0;
	return (1);
}
