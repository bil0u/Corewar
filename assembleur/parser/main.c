/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 11:51:30 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 21:48:16 by glictevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		main(int argc, char *argv[])
{
	int		fd;
	int		nb;

	if (argc == 1)
	{
		ft_printf("Usage: ./asm <sourcefile>\n");
		exit(0);
	}
	nb = 0;
	while (++nb < argc)
	{
		if ((fd = open(argv[nb], O_RDONLY)) == -1)
		{
			perror("asm");
			continue;
		}
		parse(fd, argv[nb]);
		close(fd);
	}
	return (SUCCESS);
}
