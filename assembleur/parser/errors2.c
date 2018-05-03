/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:41:58 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 20:40:41 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		unknown_instruction_error(t_lexer *lexer, char *instruction)
{
	ft_printf("%s : Error while parsing, no instructions matching name %s on \
line %d\n", FILENAME, instruction, LINE_NB);
	return (0);
}

int		unknown_label_error(t_infos *infos, char *label)
{
	ft_printf("%s : Error, no label matching name %s\n",
		infos->filename, label);
	return (-1);
}

int		wrong_argument_error(t_lexer *lexer, t_instruction *instruction,
	int arg)
{
	ft_printf("%s : Found token %s, expected one of the following token for \
arg number %d of instruction %s at pos [%d;%d]\n",
		FILENAME, get_name_tokentype(lexer->current_token->type), arg + 1,
		instruction->infos->name, LINE_NB, PREV_INDEX);
	if (instruction->infos->valid_types[arg] & 0x1)
		ft_printf("\t- REGISTER\n");
	if (instruction->infos->valid_types[arg] & 0x2)
		ft_printf("\t- DIRECT_LABEL\n");
	if (instruction->infos->valid_types[arg] & 0x4)
		ft_printf("\t- INDIRECT_LABEL\n");
	if (instruction->infos->valid_types[arg] & 0x8)
		ft_printf("\t- LABEL\n");
	return (0);
}

int		parse_line_error(t_lexer *lexer)
{
	ft_printf("%s : Error while parsing, expecting token LABEL or TEXT or \
ENDLINE, found token %s at pos [%d;%d]\n", FILENAME,
		get_name_tokentype(TOKEN->type), LINE_NB, PREV_INDEX);
	return (0);
}

int		parse_label_error(t_lexer *lexer)
{
	ft_printf("%s : Error while parsing, expecting ENDLINE or TEXT token, \
found token %s at pos [%d;%d]\n", FILENAME, get_name_tokentype(TOKEN->type),
		LINE_NB, PREV_INDEX);
	return (0);
}
