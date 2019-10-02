/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:02:54 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:04:02 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	mod_(t_data *data, int ch, int ch1, t_player *players)
{
	if ((ch1 == ' ' || ch == ' ') && data->pause == 0)
		data->pause = 1;
	else if ((ch1 == ' ' || ch == ' ') && data->pause && data->ready)
		data->pause = 0;
	else if ((ch1 == 'e' || ch == 'e') && data->sleep > -7)
		data->sleep--;
	else if ((ch1 == 'w' || ch == 'w') && data->sleep < 1)
		data->sleep++;
	else if ((ch1 == 'm' || ch == 'm') && data->mode == 0)
		data->mode = 1;
	else if ((ch1 == 'm' || ch == 'm') && data->mode == 1)
		data->mode = 0;
	else if ((ch1 == 'd' || ch == 'd') && data->mode_death == 0)
		data->mode_death = 1;
	else if ((ch1 == 'd' || ch == 'd') && data->mode_death)
		data->mode_death = 0;
	else if ((ch1 == 's' || ch == 's') && data->step == 0)
		data->step = 1;
	else if ((ch1 == 's' || ch == 's') && data->step)
		data->step = 0;
	else if (ch1 == 'q' || ch == 'q')
		vm_ncurs_quit(data, players);
}

int		vm_ncurgetch(t_data *data, t_player *players, char ch1)
{
	char ch;

	ch = wgetch(data->n_arena);
	mod_(data, ch, ch1, players);
	return (data->pause);
}

void	vm_ncur_pause(t_data *data, t_player *players, int ready)
{
	char	ch;

	if (data->pause && data->ready == ready)
	{
		while (1)
		{
			ch = wgetch(data->n_arena);
			if (ch == ' ' && data->ready == 0)
			{
				data->ready = 1;
				if (data->music.ready)
					Mix_PlayMusic(data->music.ready, 1);
				sleep(2);
				data->pause = 0;
				break ;
			}
			else if (!vm_ncurgetch(data, players, ch))
				break ;
		}
	}
}
