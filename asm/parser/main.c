/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glictevo <glictevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 11:51:30 by glictevo          #+#    #+#             */
/*   Updated: 2018/05/03 14:46:02 by upopee           ###   ########.fr       */
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
		fd = open(argv[nb], O_RDONLY);
		parse(fd, argv[nb]);
		close(fd);
	}
}
