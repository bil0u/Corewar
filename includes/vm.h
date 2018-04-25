/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:58:14 by upopee            #+#    #+#             */
/*   Updated: 2018/04/25 03:33:04 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H


/*
** -- INIT ENV AND DATA --
*/

int 		check_argv(int ac, char **av, t_cwvm *vm);
void		load_players(t_cwvm *vm);

/*
** -- UTILS --
*/

int			player_exists(uint8_t player_no, t_gamectrl *g);
t_process	*dup_process(t_vcpu *c, t_player *pl, t_process *p, uint16_t init);
void		check_gstate(t_cwvm *vm, t_gamectrl *g, t_jobctrl *j, t_vmctrl *c);

/*
** -- ARGV UTILS --
*/

int			get_nextpno(uint16_t flags);
int			is_valid_pno(t_vmctrl *ctrl, int ac, char **av, int *a);
int			is_option(char *opt);
int			is_numeric(int ac, char **av, int a);

/*
** -- VERBOSE --
*/

int			err_msg(char *msg);
int			dump_stop(t_cwvm *vm, uint32_t *breakpoint);
void		print_pcmove(uint32_t pc, uint8_t *memory, uint8_t nb_bytes);

/*
** -- DEBUG --
*/

void 		debug_game_infos(t_cwvm *vm, t_vcpu *c, t_gamectrl *g, t_vmverb *v);
void		debug_memory(uint8_t *arena, t_list *p_stack, char *win);
void		debug_process(t_cwvm *vm, t_list *p, t_jobctrl *j);

int			is_pc_val(uint32_t to_test, t_list *p_stack);

char		*get_p_color(uint8_t player_no);
char		*get_p_bgcolor(uint8_t player_no);
char		*get_p_pccolor(uint8_t player_no);

#endif
