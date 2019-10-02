/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:02:28 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:02:30 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	vm_ncur_change_color(t_data *data, int color, int process)
{
	if (!process)
		wattron(data->n_arena, COLOR_PAIR(color + 1));
	else
		wattron(data->n_arena, COLOR_PAIR(6));
}

void	vm_ncur_playm_sleep(t_data *data)
{
	if (data->ready == 1 && data->mode_death != 1)
	{
		if (data->sleep > 0)
			sleep(data->sleep);
		else if (data->sleep == 0)
			usleep(800000);
		else if (data->sleep == -1)
			usleep(600000);
		else if (data->sleep == -2)
			usleep(400000);
		else if (data->sleep == -3)
			usleep(200000);
		else if (data->sleep == -4)
			usleep(80000);
		else if (data->sleep == -5)
			usleep(60000);
		else if (data->sleep == -6)
			usleep(40000);
		else if (data->sleep == -7)
			usleep(20000);
	}
}

void	vm_ncur_putandcolor(t_data *data, int *act_color, int i)
{
	if (*act_color != data->c_arena[i] || data->p_arena[i])
	{
		vm_ncur_change_color(data, data->c_arena[i], data->p_arena[i]);
		*act_color = data->c_arena[i];
		if (data->p_arena[i])
			*act_color = -42;
	}
	if (data->p_arena[i])
	{
		wprintw(data->n_arena, "%02x", data->arena[i]);
		wattroff(data->n_arena, COLOR_PAIR(6));
		wprintw(data->n_arena, " ");
	}
	else
		wprintw(data->n_arena, "%02x ", data->arena[i]);
}

int		back_slash_n(int j[], t_data *data)
{
	j[1]++;
	if (j[1] == 64)
	{
		j[1] = 0;
		wprintw(data->n_arena, "\n");
	}
	return (1);
}

int		vm_ncur_coldump(t_data *data, t_player *player)
{
	int			i[2];
	static	int	act_color = -42;
	char		ch;

	ft_bzero(i, sizeof(i));
	werase(data->n_arena);
	while (i[0] < MEM_SIZE)
	{
		vm_ncur_putandcolor(data, &act_color, i[0]);
		i[0]++;
		back_slash_n(i, data);
	}
	data->c_dump = 0;
	wrefresh(data->n_arena);
	wrefresh(data->b_arena);
	vm_ncur_playm_sleep(data);
	if (data->step == 0)
		vm_ncur_pause(data, player, 1);
	if (data->step)
	{
		ch = wgetch(data->r_arena);
		if (ch == 's')
			data->step = 0;
	}
	return (1);
}
