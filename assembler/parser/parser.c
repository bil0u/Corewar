/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:44:36 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 20:42:31 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		parse(int fd, char *filename)
{
	t_lexer	lexer;
	t_infos	infos;
	int		tmp;

	ft_bzero(&infos, sizeof(t_infos));
	infos.filename = filename;
	if ((infos.outputfilename = get_outputfilename(filename)) == NULL)
		return (0);
	if (!initialize_lexer(&lexer, fd, filename))
	{
		free_all(&lexer, &infos);
		return (0);
	}
	if (parse_name_comment(&lexer, &infos) == 0)
		return (free_on_parse_error(&infos, &lexer));
	tmp = 1;
	while (tmp == 1)
		tmp = parse_line(&lexer, &infos);
	if (tmp == 0)
		return (free_on_parse_error(&infos, &lexer));
	tmp = write_in_file(&infos);
	if (tmp)
		ft_printf("Writing output in file : %s\n", infos.outputfilename);
	free_all(&lexer, &infos);
	return (tmp);
}

int		parse_line(t_lexer *lexer, t_infos *infos)
{
	if (check(lexer, ENDLINE))
	{
		if (!eat(lexer, ENDLINE))
			return (0);
		return (1);
	}
	if (check(lexer, LABEL))
		return (parse_label(lexer, infos));
	else if (check(lexer, TEXT))
		return (parse_instruction(lexer, infos));
	else if (check(lexer, END))
		return (-1);
	return (parse_line_error(lexer));
}

int		parse_label(t_lexer *lexer, t_infos *infos)
{
	t_label	label;
	t_list	*lst;

	if ((lst = ft_lstnew(&label, sizeof(t_label))) == NULL)
		return (malloc_fail_error(lexer));
	LST_L->name = (char *)TOKEN->value.s;
	LST_L->address = ADDR_INDEX;
	if (!eat(lexer, LABEL))
		return (0);
	ft_lstappend(&LABELS, lst);
	if (check(lexer, ENDLINE))
	{
		if (!eat(lexer, ENDLINE))
			return (0);
		return (1);
	}
	else if (check(lexer, TEXT))
		return (parse_instruction(lexer, infos));
	return (parse_label_error(lexer));
}

int		parse_instruction(t_lexer *lexer, t_infos *infos)
{
	t_instruction	instruction;
	t_list			*lst;

	ft_bzero(&instruction, sizeof(t_instruction));
	if ((lst = ft_lstnew(&instruction, sizeof(t_instruction))) == NULL)
		return (malloc_fail_error(lexer));
	LST_I->address = ADDR_INDEX;
	LST_I->infos = get_opinfos((char *)TOKEN->value.s);
	if (LST_I->infos == NULL)
	{
		free(lst->content);
		free(lst);
		return (unknown_instruction_error(lexer, TOKEN->value.s));
	}
	free(TOKEN->value.s);
	LST_I->size = LST_I->infos->has_bytecode == 1 ? 2 : 1;
	if (!eat(lexer, TEXT))
		return (0);
	ft_lstappend(&INSTRUCTIONS, lst);
	if (!parse_parameters(lexer, infos, lst))
		return (0);
	if (!eat(lexer, ENDLINE))
		return (0);
	return (1);
}

char	*get_outputfilename(char *filename)
{
	int		len;
	char	*new;

	len = ft_strlen(filename);
	if (*(filename + len - 1) == 's' && *(filename + len - 2) == '.')
	{
		new = (char *)ft_memalloc(len + 3);
		if (ft_strcpy(new, filename) == NULL)
			return (NULL);
		if (ft_strcpy(new + len - 2, ".cor") == NULL)
			return (NULL);
		return (new);
	}
	return (ft_strdup(".cor"));
}
