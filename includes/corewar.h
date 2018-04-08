/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:58:14 by upopee            #+#    #+#             */
/*   Updated: 2018/04/08 11:43:32 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# define VALID_OPT		"dsvnSVa"
# define NUMERIC_OPT	"dsvn"

int		get_nextpno(uint16_t flags);
int		is_valid_pno(int flags, int player_no);
int		is_valid_file(char *opt, t_cwdata *env);
int		is_valid_option(char *opt);
int		is_numeric(int argc, char **argv, int c);

int		load_binary(int fd, t_player *pbuff, uint8_t *mbuff);
int 	check_argv(int argc, char **argv, t_cwdata *env);
void	load_players(t_cwdata *env);

void	load_process(t_process *p, t_vcpu *cpu);
void	kill_quiet_processes(t_cwdata *env);


/*
** - _DEBUG_
*/

void	print_memory(t_cwdata *env, char *win);
void	print_registers(t_process *p, char *win);
int		err_msg(char *msg);

#endif
