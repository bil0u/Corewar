/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 02:50:22 by upopee            #+#    #+#             */
/*   Updated: 2018/03/29 07:35:00 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "corewar_types.h"
#include "cpu.h"

int				load_champion(int fd, t_player *new, uint8_t *memory)
{
	uint32_t	nbr_buff;
	uint8_t		mem_buff[CHAMP_MAX_SIZE];

	if (read(fd, &nbr_buff, MAGIC_LENGTH) != MAGIC_LENGTH
		|| (new->header.magic = SWAP_UINT32(nbr_buff)) != COREWAR_EXEC_MAGIC
		|| read(fd, new->header.prog_name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH
		|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
		|| read(fd, &nbr_buff, PROG_SZ_LENGTH) != PROG_SZ_LENGTH
		|| (new->header.prog_size = SWAP_UINT32(nbr_buff)) == 0
		|| new->header.prog_size > CHAMP_MAX_SIZE
		|| read(fd, new->header.comment, COMMENT_LENGTH) != COMMENT_LENGTH
		|| lseek(fd, SPACING_LENGTH, SEEK_CUR) == -1
		|| read(fd, mem_buff, new->header.prog_size) != new->header.prog_size)
		return (FAILURE);
	ft_printf("{yellow}Magic:{eoc}   0x%x\n", new->header.magic);
	ft_printf("{yellow}Name:{eoc}    %s\n", new->header.prog_name);
	ft_printf("{yellow}Size:{eoc}    %u\n", new->header.prog_size);
	ft_printf("{yellow}Comment:{eoc} %s\n", new->header.comment);
	ft_memcpy(memory, mem_buff, new->header.prog_size);
	return (SUCCESS);
}

// static void		set_test_values(t_vcpu *cpu, uint8_t *memory)
// {
// 	(void)memory;
// 	(void)cpu;
// 	//	TEST LIVE
// 	// memory[0] = 0x01;
// 	// memory[1] = 0x00;
// 	// memory[2] = 0x00;
// 	// memory[3] = 0x00;
// 	// memory[4] = 0x01;
//
// 	//	TEST LD [IND][REG]
// 	// memory[6] = 0x02;
// 	// memory[7] = 0b11010000;
// 	// memory[8] = 0x00;
// 	// memory[9] = 0x01;
// 	// memory[10] = 0x02;
//
// 	//	TEST LD [DIR][REG]
// 	// memory[4] = 0x02;
// 	// memory[5] = 0b10010000;
// 	// memory[6] = 0x00;
// 	// memory[7] = 0x00;
// 	// memory[8] = 0xca;
// 	// memory[9] = 0xfe;
// 	// memory[10] = 0x02;
//
// 	//	TEST ST [REG][REG]
// 	// memory[12] = 0x03;
// 	// memory[13] = 0b01010000;
// 	// memory[14] = 0x02;
// 	// memory[15] = 0x07;
//
// 	//	TEST ST [REG][IND]
// 	// memory[17] = 0x03;
// 	// memory[18] = 0b01110000;
// 	// memory[19] = 0x07;
// 	// memory[20] = 0x00;
// 	// memory[21] = 0x08;
//
// 	//	TEST ADD [REG][REG][REG]
// 		// LOAD DIRECT
// 	// 	memory[1] = 0x02;
// 	// 	memory[2] = 0b10010000;
// 	// 	memory[3] = 0x00;
// 	// 	memory[4] = 0x00;
// 	// 	memory[5] = 0x00;
// 	// 	memory[6] = 0x05;
// 	// 	memory[7] = 0x01;
// 	// memory[10] = 0x04;
// 	// memory[11] = 0b01010100;
// 	// memory[12] = 0x01;
// 	// memory[13] = 0x03;
// 	// memory[14] = 0x03;
//
// 	//	TEST SUB [REG][REG][REG]
// 		// LOAD DIRECT
// 		// memory[1] = 0x02;
// 		// memory[2] = 0b10010000;
// 		// memory[3] = 0x00;
// 		// memory[4] = 0x00;
// 		// memory[5] = 0x00;
// 		// memory[6] = 0x05;
// 		// memory[7] = 0x01;
// 		// LOAD DIRECT
// 	// 	memory[9] = 0x02;
// 	// 	memory[10] = 0b10010000;
// 	// 	memory[11] = 0x00;
// 	// 	memory[12] = 0x00;
// 	// 	memory[13] = 0x00;
// 	// 	memory[14] = 0x09;
// 	// 	memory[15] = 0x02;
// 	// memory[17] = 0x05;
// 	// memory[18] = 0b01010100;
// 	// memory[19] = 0x01;
// 	// memory[20] = 0x02;
// 	// memory[21] = 0x03;
//
// 	//	TEST AND [REG][REG][REG]
// 		// LOAD DIRECT
// 		// memory[1] = 0x02;
// 		// memory[2] = 0b10010000;
// 		// memory[3] = 0x00;
// 		// memory[4] = 0x00;
// 		// memory[5] = 0xca;
// 		// memory[6] = 0xfe;
// 		// memory[7] = 0x01;
// 		// LOAD DIRECT
// 		// memory[9] = 0x02;
// 		// memory[10] = 0b10010000;
// 		// memory[11] = 0x00;
// 		// memory[12] = 0x00;
// 		// memory[13] = 0xFF;
// 		// memory[14] = 0xFF;
// 		// memory[15] = 0x02;
// 	// memory[17] = 0x06;
// 	// memory[18] = 0b01010100;
// 	// memory[19] = 0x01;
// 	// memory[20] = 0x02;
// 	// memory[21] = 0x03;
//
// 	//	TEST AND [DIR][IND][REG]
// 	// memory[2] = 0x06;
// 	// memory[3] = 0b10110100;
// 	// memory[4] = 0x00;
// 	// memory[5] = 0x00;
// 	// memory[6] = 0x00;
// 	// memory[7] = 0x02;
// 	// memory[8] = 0x00;
// 	// memory[9] = 0x00;
// 	// memory[10] = 0x03;
//
// 	//	TEST OR [REG][REG][REG]
// 		// LOAD DIRECT
// 		// memory[1] = 0x02;
// 		// memory[2] = 0b10010000;
// 		// memory[3] = 0x00;
// 		// memory[4] = 0x00;
// 		// memory[5] = 0xc0;
// 		// memory[6] = 0xf0;
// 		// memory[7] = 0x01;
// 		// LOAD DIRECT
// 		// memory[9] = 0x02;
// 		// memory[10] = 0b10010000;
// 		// memory[11] = 0x00;
// 		// memory[12] = 0x00;
// 		// memory[13] = 0x0a;
// 		// memory[14] = 0x0e;
// 		// memory[15] = 0x02;
// 	// memory[17] = 0x07;
// 	// memory[18] = 0b01010100;
// 	// memory[19] = 0x01;
// 	// memory[20] = 0x02;
// 	// memory[21] = 0x03;
//
// 	//	TEST OR [DIR][IND][REG]
// 	// memory[2] = 0x07;
// 	// memory[3] = 0b10110100;
// 	// memory[4] = 0x00;
// 	// memory[5] = 0x00;
// 	// memory[6] = 0x00;
// 	// memory[7] = 0x01;
// 	// memory[8] = 0x00;
// 	// memory[9] = 0x00;
// 	// memory[10] = 0x03;
//
// 	//	TEST XOR [REG][REG][REG]
// 		// LOAD DIRECT
// 		// memory[1] = 0x02;
// 		// memory[2] = 0b10010000;
// 		// memory[3] = 0x00;
// 		// memory[4] = 0x00;
// 		// memory[5] = 0xca;
// 		// memory[6] = 0x0e;
// 		// memory[7] = 0x01;
// 		// LOAD DIRECT
// 		// memory[9] = 0x02;
// 		// memory[10] = 0b10010000;
// 		// memory[11] = 0x00;
// 		// memory[12] = 0x00;
// 		// memory[13] = 0xc0;
// 		// memory[14] = 0xf0;
// 		// memory[15] = 0x02;
// 	// memory[17] = 0x08;
// 	// memory[18] = 0b01010100;
// 	// memory[19] = 0x01;
// 	// memory[20] = 0x02;
// 	// memory[21] = 0x03;
//
// 	//	TEST XOR [DIR][IND][REG]
// 	// memory[2] = 0x08;
// 	// memory[3] = 0b10110100;
// 	// memory[4] = 0x00;
// 	// memory[5] = 0x00;
// 	// memory[6] = 0x00;
// 	// memory[7] = 0x03;
// 	// memory[8] = 0x00;
// 	// memory[9] = 0x00;
// 	// memory[10] = 0x03;
//
// 	//	TEST ZJMP [DIR]
// 	// cpu->carry = 1;
// 	// memory[5] = 0x09;
// 	// *((uint32_t *)(memory + 6)) = SWAP_UINT32((uint32_t)-2);
//
// 	// TEST LDI [IND][DIR][REG]
// 		// TEST VALUES
// 		// memory[25] = 0x00;
// 		// memory[26] = 0x00;
// 		// memory[27] = 0x00;
// 		// memory[28] = 0x05;
// 		// TEST VALUES
// 		// memory[30] = 0x00;
// 		// memory[31] = 0x00;
// 		// memory[32] = 0xca;
// 		// memory[33] = 0xfe;
// 	// memory[1] = 0x0a;
// 	// memory[2] = 0b11100100;
// 	// memory[3] = 0x00;
// 	// memory[4] = 0x18;
// 	// memory[5] = 0x00;
// 	// memory[6] = 0x00;
// 	// memory[7] = 0x00;
// 	// memory[8] = 0x18;
// 	// memory[9] = 0x03;
//
// 	// TEST STI [REG][IND][DIR]
// 		// TEST VALUES
// 		// memory[4] = 0x02;
// 		// memory[5] = 0b10010000;
// 		// memory[6] = 0x00;
// 		// memory[7] = 0x00;
// 		// memory[8] = 0xca;
// 		// memory[9] = 0xfe;
// 		// memory[10] = 0x02;
// 		// TEST VALUES
// 		// memory[25] = 0x00;
// 		// memory[26] = 0x00;
// 		// memory[27] = 0x00;
// 		// memory[28] = 0x05;
// 	// memory[15] = 0x0b;
// 	// memory[16] = 0b01111000;
// 	// memory[17] = 0x02;
// 	// memory[18] = 0x00;
// 	// memory[19] = 0x0a;
// 	// memory[20] = 0x00;
// 	// memory[21] = 0x00;
// 	// memory[22] = 0x00;
// 	// memory[23] = 0x0e;
//
// 	//	TEST LLD [IND][REG]
// 		// memory[31] = 0x00;
// 		// memory[32] = 0x00;
// 		// memory[33] = 0xca;
// 		// memory[34] = 0xfe;
// 		// TEST LD [IND][REG]
// 		// memory[11] = 0x02;
// 		// memory[12] = 0b11010000;
// 		// memory[13] = 0x00;
// 		// memory[14] = 0x14;
// 		// memory[15] = 0x02;
// 	// memory[1] = 0x0d;
// 	// memory[2] = 0b11010000;
// 	// memory[3] = 0x00;
// 	// memory[4] = 0x1e;
// 	// memory[5] = 0x02;
//
// 	// TEST LLDI [IND][DIR][REG]
// 		// TEST VALUES
// 		// memory[25] = 0x00;
// 		// memory[26] = 0x00;
// 		// memory[27] = 0x00;
// 		// memory[28] = 0x05;
// 		// TEST VALUES
// 		// memory[30] = 0x00;
// 		// memory[31] = 0x00;
// 		// memory[32] = 0xca;
// 		// memory[33] = 0xfe;
// 	// memory[1] = 0x0e;
// 	// memory[2] = 0b11100100;
// 	// memory[3] = 0x00;
// 	// memory[4] = 0x18;
// 	// memory[5] = 0x00;
// 	// memory[6] = 0x00;
// 	// memory[7] = 0x00;
// 	// memory[8] = 0x18;
// 	// memory[9] = 0x03;
//
// 	// TEST AFF
// 		// LOAD TEST VALUE
// 		// memory[4] = 0x02;
// 		// memory[5] = 0b10010000;
// 		// memory[6] = 0x00;
// 		// memory[7] = 0x00;
// 		// memory[8] = 0x1B;
// 		// memory[9] = 0x41;
// 		// memory[10] = 0x02;
// 	// memory[12] = 0x10;
// 	// memory[13] = 0b01000000;
// 	// memory[14] = 0x02;
// }

int				main(int argc, char **argv)
{
	uint8_t		memory[MEM_SIZE];
	uint32_t	registers[REG_NUMBER];
	t_vcpu		cpu;
	t_player	player;

	ft_bzero(&memory, MEM_SIZE);
	ft_bzero(&registers, REG_LEN);
	ft_bzero(&cpu, sizeof(cpu));

	if (argc > 1)
	{
		int			fd;

		if ((fd = open(argv[1], O_RDONLY)) != -1)
		{
			ft_bzero(&player, sizeof(player));
			if (load_champion(fd, &player, memory) == SUCCESS)
				ft_printf("{green}LOAD OK{eoc}\n");
			else
				ft_printf("{red}LOAD KO{eoc}\n");
			close(fd);
		}
	}

	new_logwindow("mem", WF_KEEP | WF_CLOSE);
	new_logwindow("reg", WF_KEEP | WF_CLOSE);
	new_logwindow("ins", WF_KEEP | WF_CLOSE);

	init_cpu(&cpu, memory);
	// set_test_values(&cpu, memory);
	load_process(&cpu, registers, 0);
	run_cpu(&cpu, 10, 1, 1);

	return (0);
}
