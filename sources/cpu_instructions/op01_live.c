/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op01_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:17:53 by upopee            #+#    #+#             */
/*   Updated: 2018/05/01 19:30:04 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cpu_types.h"
#include "vm_types.h"
#include "cpu.h"
#include "vm.h"
#include "cpu_verbose.h"
#include "cpu_debug.h"

static void	valid_live(t_vcpu *cpu, t_player *alv, t_gamectrl *g, t_process *p)
{
	uint32_t	nbl;

	++g->valid_lives;
	nbl = ++alv->nb_lives;
	g->winner = alv->player_no;
	alv->last_live = cpu->tick;
	INS_DEB ? log_this(IDW, D_LIVEPL, IDA, p->pid, alv->player_no) : 0;
	LIV_VERB ? ft_printf(V_ALIVE, alv->player_no, alv->header.pname) : 0;
	if (g->alpha == 0 || nbl > g->players[g->alpha - 1].nb_lives)
		g->alpha = alv->player_no;
	else if (g->alpha != alv->player_no
	&& nbl == g->players[g->alpha - 1].nb_lives)
		g->alpha = 0;
}

int			live_instr(t_vcpu *cpu, t_process *p, t_player *pl, t_gamectrl *g)
{
	uint32_t	alive;

	secure_fetch(CPU_MEM, jump_to(p->pc, OPBC_SIZE), CPU_ARG, ARG_DIRSZ);
	ARG_DEB ? log_this(ADW, D_ARG_DIR, 1, CPU_ARG[0]) : 0;
	INS_VERB ? ft_printf(V_LIVE, IVA, CPU_ARG[0]) : 0;
	alive = REG_MAXVALUE - TOI32(CPU_ARG[0]) + 1;
	p->last_live = cpu->tick;
	++g->tot_lives;
	(void)pl;
	if (alive > 0 && alive <= MAX_PLAYERS
	&& player_exists(TOU8(alive), g))
		valid_live(cpu, g->players + alive - 1, g, p);
	else
		INS_DEB ? log_this(IDW, D_LIVEPR, IDA, p->pid) : 0;
	return (ARG_DIRSZ);
}
