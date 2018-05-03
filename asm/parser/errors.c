/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 12:54:21 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 14:45:45 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		malloc_fail_error(t_lexer *lexer)
{
	ft_printf("%s : malloc failed\n", FILENAME);
	ft_printf("LINE : %d\n", LINE_NB);
	ft_printf("TOKEN : %s\n", get_name_tokentype(TOKEN->type));
	return (0);
}

int		name_missing_error(t_lexer *lexer)
{
	ft_printf("%s : NAME_CMD_STRING is missing\n", FILENAME);
	return (0);
}

int		missing_closing_quote_error(t_lexer *lexer)
{
	ft_printf("%s : Missing closing quote for name or comment\n", FILENAME);
	return (0);
}

int		comment_missing_error(t_lexer *lexer)
{
	ft_printf("%s : COMMENT_CMD_STRING is missing\n", FILENAME);
	return (0);
}

int		eat_error(t_lexer *lexer, t_token_type token)
{
	ft_printf("%s : Lexical error : expected %s, got %s at pos [%d;%d]\n",
		FILENAME, get_name_tokentype(token), get_name_tokentype(TOKEN->type),
			LINE_NB, PREV_INDEX);
	return (0);
}
