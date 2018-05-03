/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:43:29 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 14:45:59 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_all(t_lexer *lexer, t_infos *infos)
{
	ft_lstdel(&infos->labels, free_labels);
	ft_lstdel(&infos->instructions, free_instructions);
	free(infos->outputfilename);
	free(lexer->current_token);
}

void	free_labels(void *content, size_t content_size)
{
	content_size++;
	free(((t_label *)content)->name);
	ft_memdel(&content);
}

void	free_instructions(void *content, size_t content_size)
{
	int		arg;

	content_size++;
	arg = -1;
	ft_memdel(&content);
}

int		free_on_write_error(t_list *lst, int arg, char *buf)
{
	free(buf);
	free(LST_I->params[arg].value.s);
	while (++arg < LST_I->infos->nb_args)
		if (LST_I->params[arg].valuetype == 's')
			free(LST_I->params[arg].value.s);
	lst = lst->next;
	while (lst)
	{
		arg = -1;
		while (++arg < LST_I->infos->nb_args)
			if (LST_I->params[arg].valuetype == 's')
				free(LST_I->params[arg].value.s);
		lst = lst->next;
	}
	return (0);
}

int		free_on_parse_error(t_infos *infos, t_lexer *lexer)
{
	int		arg;
	t_list	*lst;

	if (TOKEN->valuetype == 's')
		free(TOKEN->value.s);
	lst = infos->instructions;
	while (lst)
	{
		arg = -1;
		while (++arg < LST_I->infos->nb_args)
			if (LST_I->params[arg].valuetype == 's')
				free(LST_I->params[arg].value.s);
		lst = lst->next;
	}
	while (TOKEN->type != END)
		call_gnl(lexer);
	free_all(lexer, infos);
	return (0);
}
