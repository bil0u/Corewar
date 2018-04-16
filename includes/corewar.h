/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:58:14 by upopee            #+#    #+#             */
/*   Updated: 2018/04/16 15:29:40 by upopee           ###   ########.fr       */
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
int		is_valid_file(char *opt, t_cwvm *vm);
int		is_valid_option(char *opt);
int		is_numeric(int argc, char **argv, int c);
int 	check_argv(int argc, char **argv, t_cwvm *vm);

/*
** -- INIT ENV AND DATA --
*/

int		load_binary(int fd, t_player *p_data);
void	load_players(t_cwvm *vm);

/*
** -- MAIN LOOP UTILS --
*/

void	check_gamestatus(t_cwvm *vm);
int		dump_stop(t_cwvm *vm, int32_t *breakpoint);

/*
** -- DEBUG_ --
*/

void	print_memory(uint8_t *arena, t_list *p_stack, char *win);
void	print_registers(t_player *pl, t_process *pending, char *win);
int		is_pc_val(uint32_t to_test, t_list *p_stack);
int		err_msg(char *msg);

#endif
