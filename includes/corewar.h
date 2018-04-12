/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:58:14 by upopee            #+#    #+#             */
/*   Updated: 2018/04/12 06:08:24 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# define VALID_OPT		"dsvnSVa"
# define NUMERIC_OPT	"dsvnS"

/*
** -- LOADING ARGUMENTS --
*/

int		get_nextpno(uint16_t flags);
int		is_valid_pno(int flags, int player_no);
int		is_valid_file(char *opt, t_cwdata *env);
int		is_valid_option(char *opt);
int		is_numeric(int argc, char **argv, int c);
int 	check_argv(int argc, char **argv, t_cwdata *env);

/*
** -- INIT ENV AND DATA --
*/

int		load_binary(int fd, t_player *pbuff, uint8_t *mbuff);
void	load_players(t_cwdata *env, t_player *p);

/*
** -- MAIN LOOP UTILS --
*/

void	load_process(t_process *p, t_vcpu *cpu);
void	refresh_process_status(t_cwdata *env, t_pcontrol *ctrl);
int		dump_stop(t_cwdata *env, uint16_t flags, uint64_t *breakpoint);

/*
** -- DEBUG_ --
*/

void	print_memory(uint8_t *arena, t_list *processes, char *win);
void	print_registers(t_player *pl, t_process *pr, char *win);
int		is_pc_val(uint32_t to_test, t_list *curr_process);
int		err_msg(char *msg);

#endif
