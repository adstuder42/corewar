/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_side.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:02:50 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/21 13:04:32 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	vm_logoput(t_data *data)
{
	wattron(data->r_arena, COLOR_PAIR(8));
	wprintw(data->r_arena, " ____                         ");
	wprintw(data->r_arena, "__      __                    \n");
	wprintw(data->r_arena, "/\\  _`\\                      /\\ \\  ");
	wprintw(data->r_arena, "__/\\ \\                   \n");
	wprintw(data->r_arena, "\\ \\ \\/\\_\\    ___   _ __    ");
	wprintw(data->r_arena, "__\\ \\ \\/\\ \\ \\ \\     __     _ __");
	wprintw(data->r_arena, "  \n");
	wprintw(data->r_arena, " \\ \\ \\/_/_  / __`\\/\\` ");
	wprintw(data->r_arena, "__\\/ __`\\ \\ \\ \\ \\ \\ \\  / __`\\  /");
	wprintw(data->r_arena, "\\` __\\\n");
	wprintw(data->r_arena, "  \\ \\ \\L\\ \\/\\ \\L\\ \\ ");
	wprintw(data->r_arena, "\\ \\//\\  __/\\ \\ \\_/ \\_\\ \\/\\ \\L");
	wprintw(data->r_arena, "\\.\\_\\ \\ \\/ \n");
	wprintw(data->r_arena, "   \\ \\____/\\ \\____/\\ \\_\\\\");
	wprintw(data->r_arena, " \\____\\\\ `\\___x___/\\ \\__/.\\_");
	wprintw(data->r_arena, "\\\\ \\_\\ \n");
	wprintw(data->r_arena, "    \\/___/  \\/___/  \\/_/ \\/____/");
	wprintw(data->r_arena, "  \\/__//__/  \\/__/\\/_/ \\/_/ \n");
	wprintw(data->r_arena, "\n\n");
	wattroff(data->r_arena, COLOR_PAIR(8));
}

void	vm_ncurside_status(t_data *data)
{
	if (data->pause)
		wprintw(data->r_arena,
		"---------------------------- STATUS ------------------------------"
		"\n\n\tPAUSE\n\n");
	else
		wprintw(data->r_arena,
		"---------------------------- STATUS ------------------------------"
		"\n\n\tFIGHT\n\n");
}

void	vm_ncurside_mode(t_data *data)
{
	wprintw(data->r_arena,
		"----------------------------- MODE -------------------------------");
	if (data->mode && data->mode_death == 0 && data->step == 0)
		wprintw(data->r_arena, "\n\n\tPLAY\n\n");
	else if (data->mode == 0 && data->mode_death == 0 && data->step == 0)
		wprintw(data->r_arena, "\n\n\tEXEC\n\n");
	else if (data->mode_death && data->step == 0)
		wprintw(data->r_arena, "\n\n\tDEATH\n\n");
	else if (data->step)
		wprintw(data->r_arena, "\n\n\tSTEP\n\n");
}

void	vm_speedput(t_data *data)
{
	wprintw(data->r_arena,
		"----------------------------- SPEED ------------------------------"
		"\n\n");
	getyx(data->r_arena, data->yspeed, data->xspeed);
	if (data->sleep > 0)
		wprintw(data->r_arena, "\t%d s. sleep\n\n", data->sleep);
	else if (data->sleep == 0)
		wprintw(data->r_arena, "\t0.8 s. sleep\n\n");
	else if (data->sleep == -1)
		wprintw(data->r_arena, "\t0.6 s. sleep\n\n");
	else if (data->sleep == -2)
		wprintw(data->r_arena, "\t0.4 s. sleep\n\n");
	else if (data->sleep == -3)
		wprintw(data->r_arena, "\t0.2 s. sleep\n\n");
	else if (data->sleep == -4)
		wprintw(data->r_arena, "\t0.08 s. sleep\n\n");
	else if (data->sleep == -5)
		wprintw(data->r_arena, "\t0.06 s. sleep\n\n");
	else if (data->sleep == -6)
		wprintw(data->r_arena, "\t0.04 s. sleep\n\n");
	else if (data->sleep == -7)
		wprintw(data->r_arena, "\t0.02 s. sleep\n\n");
}

void	vm_ncurside_process(t_data *data, t_player *player)
{
	int			i;
	int			j;
	t_process	*process;
	int			sum;

	wprintw(data->r_arena,
	"---------------------------- PROCESS -----------------------------\n\n");
	i = 0;
	sum = 0;
	while (i < data->nbr_of_players)
	{
		if ((player + i)->alive)
		{
			j = 0;
			process = data->init_process[i];
			while (process != NULL)
			{
				j++;
				process = process->next;
			}
			sum += j;
		}
		i++;
	}
	wprintw(data->r_arena, "\tTotal processes\t: %d\n\n", sum);
}
