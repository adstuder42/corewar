/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_side_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:02:45 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:02:46 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	print_players_state(t_data *data, t_player *players, int i)
{
	wprintw(data->r_arena, "\tPlayer : %d\n", (players + i)->num);
	wprintw(data->r_arena, "\tName : ");
	wattron(data->r_arena, COLOR_PAIR(i + 2));
	wprintw(data->r_arena, "%-128s\n", (players + i)->name);
	wattroff(data->r_arena, COLOR_PAIR(i + 2));
	wprintw(data->r_arena, "\tLives Count : %d\n\n",
			(players + i)->live_count);
}

void	vm_ncurside_players(t_data *data, t_player *players)
{
	int		i;

	wprintw(data->r_arena,
			"---------------------------- PLAYERS -----------------------------"
			"\n\n");
	i = 0;
	while (i < data->nbr_of_players)
	{
		if ((players + i)->alive)
			print_players_state(data, players, i);
		else
		{
			wprintw(data->r_arena, "\u2620\tPlayer : %d\n",
					(players + i)->num);
			wprintw(data->r_arena, "\tName : ");
			wattron(data->r_arena, COLOR_PAIR(i + 2));
			wprintw(data->r_arena, "%-128s\n", (players + i)->name);
			wattroff(data->r_arena, COLOR_PAIR(i + 2));
			wprintw(data->r_arena, "\tLives Count : %d\n\n",
					(players + i)->live_count);
		}
		i++;
	}
}

void	vm_ncursideput(t_data *data, int cycle, t_player *players)
{
	vm_logoput(data);
	vm_ncurside_status(data);
	vm_ncurside_mode(data);
	vm_speedput(data);
	wprintw(data->r_arena,
			"----------------------------- CYCLE ------------------------------"
			"\n\n\t%d cycles\n\n", cycle);
	vm_ncurside_process(data, players);
	vm_ncurside_players(data, players);
	wprintw(data->r_arena,
			"----------------------------- LIVES ------------------------------"
			"\n\n");
	wprintw(data->r_arena,
			"\tTIME TO CHECK IF ALIVE\t: %d\n\n", data->live_checker_countdown);
}
