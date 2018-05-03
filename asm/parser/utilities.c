/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:32:02 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 14:46:24 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../includes/instructions.h"

t_op	*get_opinfos(char *name)
{
	int		index;

	index = -1;
	while (++index < NB_INSTRUCTIONS)
		if (!ft_strcmp(g_op_set[index].name, name))
			return (&(g_op_set[index]));
	return (NULL);
}

char	*get_name_opcode(int n)
{
	if (n < 0 || n > NB_INSTRUCTIONS)
		return (NULL);
	return (g_op_set[n].name);
}

void	pass_spaces(t_lexer *lexer)
{
	while (ft_iswhitespace(*(LINE + INDEX)) == 1)
		INDEX++;
}

char	*get_name_argtype(int n)
{
	if (n == 1)
		return ("REGISTER");
	if (n == 2)
		return ("DIRECT_LABEL");
	if (n == 4)
		return ("INDIRECT_LABEL");
	if (n == 8)
		return ("LABEL");
	return ("wut");
}

char	*get_name_tokentype(t_token_type token)
{
	if (token == 0)
		return ("NAME");
	if (token == 1)
		return ("COMMENT");
	if (token == 2)
		return ("DIRECT_LABEL");
	if (token == 3)
		return ("INDIRECT_LABEL");
	if (token == 4)
		return ("LABEL");
	if (token == 5)
		return ("TEXT");
	if (token == 6)
		return ("REGISTER");
	if (token == 7)
		return ("SEPARATOR");
	if (token == 8)
		return ("ENDLINE");
	if (token == 9)
		return ("END");
	if (token == 10)
		return ("ERROR");
	return ("wut");
}
