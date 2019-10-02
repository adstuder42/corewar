/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_war.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:02:59 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:03:00 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	vm_ncurs_end(t_data *data, int cycle, t_player *players)
{
	char	ch;

	werase(data->r_arena);
	vm_ncursideput(data, cycle, players);
	wrefresh(data->r_arena);
	wprintw(data->b_arena, "War over! \n");
	sleep(3);
	wrefresh(data->b_arena);
	if (data->music.win)
		Mix_PlayMusic(data->music.win, 1);
	while (1)
	{
		ch = wgetch(data->n_arena);
		if (ch == 'q')
			vm_ncurs_quit(data, players);
	}
}

void	vm_ncur_before_fight(t_data *data, int cycle, t_player *players)
{
	if (data->vis)
	{
		werase(data->r_arena);
		if ((cycle + 1) % 50 == 0)
			werase(data->b_arena);
		vm_ncurgetch(data, players, 0);
		vm_ncursideput(data, cycle, players);
		if (data->live_checker_countdown == 0)
			wrefresh(data->r_arena);
	}
}

void	vm_ncur_after_fight(t_data *data, int cycle, t_player *players)
{
	if (data->vis)
	{
		if (data->mode == 0)
			(data->c_dump) ? vm_ncur_coldump(data, players) : 0;
		else
			vm_ncur_coldump(data, players);
		wrefresh(data->r_arena);
		if (data->step == 0)
			vm_ncur_pause(data, players, 0);
		if (cycle % 50 == 0)
			wrefresh(data->b_arena);
	}
}
