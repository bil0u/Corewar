/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:04:39 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 20:38:58 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		parse_name_comment(t_lexer *lexer, t_infos *infos)
{
	if (parse_name(lexer, infos) == 0
	|| eat(lexer, ENDLINE) == 0
	|| parse_comment(lexer, infos) == 0
	|| eat(lexer, ENDLINE) == 0)
		return (0);
	return (1);
}

int		parse_name(t_lexer *lexer, t_infos *infos)
{
	while (check(lexer, ENDLINE))
		eat(lexer, ENDLINE);
	if (!check(lexer, NAME))
		return (name_missing_error(lexer));
	ft_bzero(infos->header.pname, PROG_NAME_LENGTH);
	if (ft_strlen((char *)lexer->current_token->value.s) > PROG_NAME_LENGTH)
	{
		ft_printf("Champion name too long (max length %d)\n", PROG_NAME_LENGTH);
		return (0);
	}
	ft_strcpy(infos->header.pname, (char *)lexer->current_token->value.s);
	free(lexer->current_token->value.s);
	if (eat(lexer, NAME) == 0)
		return (0);
	return (1);
}

int		parse_comment(t_lexer *lexer, t_infos *infos)
{
	while (check(lexer, ENDLINE))
		eat(lexer, ENDLINE);
	if (!check(lexer, COMMENT))
		return (comment_missing_error(lexer));
	ft_bzero(infos->header.comment, COMMENT_LENGTH);
	if (ft_strlen((char *)lexer->current_token->value.s) > COMMENT_LENGTH)
	{
		ft_printf("Champion comment too long (Max length %d)\n",
			COMMENT_LENGTH);
		return (0);
	}
	ft_strcpy(infos->header.comment, (char *)lexer->current_token->value.s);
	free(lexer->current_token->value.s);
	if (eat(lexer, COMMENT) == 0)
		return (0);
	return (1);
}
