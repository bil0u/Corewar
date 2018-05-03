/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 17:41:11 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 20:39:14 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		write_in_file(t_infos *infos)
{
	char	*buf;
	int		index;
	long	tmp;

	buf = (char *)ft_memalloc(sizeof(uint32_t) * 2 + sizeof(char) *
			(PROG_NAME_LENGTH + COMMENT_LENGTH + infos->address_index) + 8);
	index = 0;
	tmp = SWAP_UINT32((long)COREWAR_EXEC_MAGIC);
	ft_memcpy(buf, &tmp, 4);
	index += sizeof(unsigned int);
	ft_memcpy(buf + index, infos->header.pname, PROG_NAME_LENGTH);
	index += PROG_NAME_LENGTH;
	ft_memcpy(buf + index, "\0\0\0\0", 4);
	index += 4;
	tmp = SWAP_UINT32(infos->address_index);
	ft_memcpy(buf + index, &tmp, 4);
	index += sizeof(unsigned int);
	ft_memcpy(buf + index, infos->header.comment, COMMENT_LENGTH);
	index += COMMENT_LENGTH;
	ft_memcpy(buf + index, "\0\0\0\0", 4);
	index += 4;
	return (write_in_file2(infos, buf, index));
}

int		write_in_file2(t_infos *infos, char *buf, int index)
{
	t_list		*lst;

	lst = INSTRUCTIONS;
	while (lst)
	{
		buf[index++] = LST_I->infos->op_number;
		if (LST_I->infos->has_bytecode == 1)
			buf[index++] = get_codage(LST_I);
		if (loop_args(infos, buf, &index, lst) == 0)
			return (0);
		lst = lst->next;
	}
	return (write_in_file3(infos, buf));
}

int		loop_args(t_infos *infos, char *buf, int *index, t_list *lst)
{
	int		arg;
	int		addr_label;

	arg = -1;
	while (++arg < LST_I->infos->nb_args)
	{
		if (LST_I->params[arg].valuetype == 's')
		{
			addr_label = find_address_label(LST_I->params[arg].value.s, infos);
			if (addr_label == -1)
				return (free_on_write_error(lst, arg, buf));
			free(LST_I->params[arg].value.s);
			LST_I->params[arg].value.i = addr_label - LST_I->address;
		}
		if (LST_I->params[arg].value.i < 0)
			LST_I->params[arg].value.i = UINT_MAX +
				LST_I->params[arg].value.i + 1;
		if (LST_I->params[arg].type & 0x1)
			write_register(buf, index, lst, arg);
		if (LST_I->params[arg].type & 0x2)
			write_direct_label(buf, index, lst, arg);
		if (LST_I->params[arg].type & 0x4)
			write_indirect_label(buf, index, lst, arg);
	}
	return (1);
}

int		write_in_file3(t_infos *infos, char *buf)
{
	int		fd;
	int		index;
	int		len;

	if ((fd = open(infos->outputfilename, O_WRONLY | O_CREAT, 0766)) < 1)
	{
		free(buf);
		ft_printf("Error while trying to write on file %s\n",
			infos->outputfilename);
		return (0);
	}
	index = -1;
	len = sizeof(unsigned int) * 2 + sizeof(char) *
		(PROG_NAME_LENGTH + COMMENT_LENGTH + infos->address_index + 8);
	while (++index < len)
		ft_dprintf(fd, "%c", *(buf + index));
	close(fd);
	free(buf);
	return (1);
}
