/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:58:14 by upopee            #+#    #+#             */
/*   Updated: 2018/04/18 08:39:07 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H


/*
** -- INIT ENV AND DATA --
*/

int 	check_argv(int ac, char **av, t_cwvm *vm);
void	load_players(t_cwvm *vm);

/*
** -- MAIN LOOP UTILS --
*/

void	check_gamestatus(t_cwvm *vm);
int		dump_stop(t_cwvm *vm, int32_t *breakpoint);

/*
** -- ARGV UTILS --
*/

int		get_nextpno(uint16_t flags);
int		is_valid_pno(t_vmctrl *ctrl, int ac, char **av, int *a);
int		is_option(char *opt);
int		is_numeric(int ac, char **av, int a);

/*
** -- DEBUG_ UTILS --
*/

void 	print_game_infos(t_cwvm *vm, t_vcpu *cpu, t_gamectrl *game);
void	print_memory(uint8_t *arena, t_list *p_stack, char *win);
void	print_registers(t_player *pl, t_process *pending, char *win);

int		is_pc_val(uint32_t to_test, t_list *p_stack);
int		err_msg(char *msg);

char	*get_p_color(uint8_t player_no);
char	*get_p_bgcolor(uint8_t player_no);
char	*get_p_pccolor(uint8_t player_no);

#endif
