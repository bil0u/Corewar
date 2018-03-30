/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/03/31 00:07:12 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "cpu.h"
#include "corewar_types.h"
#include "corewar_verbose.h"

static int	load_champion(int fd, t_player *new, uint8_t *arena)
{
	uint32_t	nbr_buff;
	uint8_t		mem_buff[CHAMP_MAX_SIZE];

	ft_bzero(new, sizeof(*new));
	if (read(fd, &nbr_buff, MAGIC_LENGTH) != MAGIC_LENGTH
	|| (new->header.magic = SWAP_UINT32(nbr_buff)) != COREWAR_EXEC_MAGIC
	|| read(fd, new->header.prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, &nbr_buff, PROG_SZ_LENGTH) != PROG_SZ_LENGTH
	|| (new->header.prog_size = SWAP_UINT32(nbr_buff)) == 0
	|| new->header.prog_size > CHAMP_MAX_SIZE
	|| read(fd, new->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH
	|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
	|| read(fd, mem_buff, new->header.prog_size + 1) != new->header.prog_size)
		return (FAILURE);
	ft_memcpy(arena, mem_buff, new->header.prog_size);
	return (SUCCESS);
}

static int	introduce_champions(uint8_t *arena, t_player *players,
										int champ_no, char **files)
{
	int			fd;
	int			load_ret;

	while (champ_no-- > 0)
	{
		if ((fd = open(files[champ_no], O_RDONLY)) == -1)
		{
			log_this("chp", LF_ERR, CW_ERR_OPEN, files[champ_no]);
			return (FAILURE);
		}
		load_ret = load_champion(fd, players + champ_no, arena);
		close(fd);
		if (load_ret == FAILURE)
		{
			log_this("chp", LF_ERR, CW_FILE_KO, files[champ_no]);
			return (FAILURE);
		}
		log_this("chp", LF_INFO, CW_FILE_OK, players[champ_no].header.prog_name,
			players[champ_no].header.comment);
	}
	return (SUCCESS);
}

static int	init_arena(uint8_t *arena, t_player *players,
									int nb_champs, char **files)
{
	if (nb_champs == 0 || nb_champs > MAX_PLAYERS)
	{
		log_this(NULL, LF_ERR, CW_CHAMPS_ERR, nb_champs, MAX_PLAYERS);
		return (FAILURE);
	}
	else if (introduce_champions(arena, players, nb_champs, files) == FAILURE)
	{
		log_this(NULL, LF_ERR, CW_LOAD_ERR);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	init_env(t_vcpu *cpu, uint8_t *arena,
							t_player *players, uint32_t *registers)
{
	ft_bzero(cpu, sizeof(*cpu));
	ft_bzero(arena, MEM_SIZE * sizeof(*arena));
	ft_bzero(players, MAX_PLAYERS * sizeof(*players));
	ft_bzero(registers, REG_NUMBER * sizeof(*registers));
	cpu->memory = arena;
	cpu->registers = registers;
}

int			main(int argc, char **argv)
{
	uint32_t	registers[REG_NUMBER];
	uint8_t		arena[MEM_SIZE];
	t_player	players[MAX_PLAYERS];
	t_vcpu		cpu;

	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);
	new_logwindow("chp", WF_KEEP | WF_CLOSE);
	//sleep(2);

	init_env(&cpu, arena, players, registers);
	if (init_arena(arena, players, argc - 1, &argv[1]) == FAILURE)
		return (FAILURE);

	run_cpu(&cpu, 10, 1, 1);
	return (SUCCESS);
}
