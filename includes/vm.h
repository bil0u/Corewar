/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 01:58:14 by upopee            #+#    #+#             */
/*   Updated: 2018/04/27 19:30:13 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
** -- INIT ENV AND DATA --
*/

int			check_argv(int ac, char **av, t_cwvm *vm);
void		load_players(t_cwvm *vm);
int			init_vm(int argc, char **argv, t_cwvm *vm);
void		init_data(t_cwvm *vm);

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

void		debug_infos(t_cwvm *vm, t_vcpu *c, t_gamectrl *g, t_vmverb *v);
void		debug_memory(uint8_t *arena, uint8_t *a_flags, char *win);
void		debug_processes(t_cwvm *vm, t_list *curr, t_jobctrl *jobs);
void		debug_registers(t_vmverb *verb, t_list *curr);

int			is_pc_val(uint32_t to_test, t_list *p_stack);

uint8_t		get_pno(uint8_t a_flags);
char		*get_timercolor(uint16_t timer);
char		*get_p_color(uint8_t player_no);
char		*get_p_bgcolor(uint8_t player_no);
char		*get_p_pccolor(uint8_t player_no);

#endif
