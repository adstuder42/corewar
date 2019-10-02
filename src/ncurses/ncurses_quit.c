/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:02:40 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:02:41 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	vm_quit_sdl(t_data *data)
{
	Mix_HaltMusic();
	if (data->music.fork)
		Mix_FreeMusic(data->music.fork);
	if (data->music.ready)
		Mix_FreeMusic(data->music.ready);
	if (data->music.death)
		Mix_FreeMusic(data->music.death);
	if (data->music.win)
		Mix_FreeMusic(data->music.win);
	Mix_CloseAudio();
	Mix_Quit();
}

void	vm_ncurs_quit(t_data *data, t_player *players)
{
	vm_quit_sdl(data);
	kill_every_one(players, data);
	delwin(data->b_arena);
	delwin(data->n_arena);
	delwin(data->r_arena);
	delwin(data->rb_arena);
	endwin();
	exit(EXIT_SUCCESS);
}
