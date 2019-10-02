/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:02:35 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:02:36 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	vm_init_sdl(t_data *data)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		ft_printf("unable to initialize SDL\n");
		exit(EXIT_FAILURE);
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		ft_printf("unable to initialize audio\n");
		exit(EXIT_FAILURE);
	}
	Mix_AllocateChannels(1);
	data->music.fork = Mix_LoadMUS("sounds/output.wav");
	data->music.ready = Mix_LoadMUS("sounds/ready.wav");
	data->music.death = Mix_LoadMUS("sounds/death.wav");
	data->music.win = Mix_LoadMUS("sounds/win.wav");
}

void	vm_init_ncurscol(void)
{
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_color(BRIGHT_WHITE, 1000, 1000, 1000);
	init_pair(7, BRIGHT_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
}

void	cmd_(t_data *data)
{
	wprintw(data->rb_arena,
	"--------------------------- COMMANDS -----------------------------\n\n");
	wprintw(data->rb_arena, "\tPAUSE/PLAY\t\t: SPACEBAR\n");
	wprintw(data->rb_arena, "\tSPEED++\t\t\t: E\n");
	wprintw(data->rb_arena, "\tSPEED--\t\t\t: W\n");
	wprintw(data->rb_arena, "\tMODE PLAY/EXEC Toggle\t: M\n");
	wprintw(data->rb_arena, "\tMODE DEATH Toggle\t: D\n");
	wprintw(data->rb_arena, "\tMODE STEP Toggle\t: S\n");
	wprintw(data->rb_arena, "\tQUIT\t\t\t: Q\n");
}

void	vm_init_ncurses(t_data *data)
{
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	curs_set(0);
	vm_init_ncurscol();
	bkgd(COLOR_PAIR(8));
	data->n_arena = newwin(64, 195, 2, 5);
	nodelay(data->n_arena, TRUE);
	data->b_arena = newwin(40, 195, 68, 5);
	data->rb_arena = newwin(20, 66, 68, 205);
	wbkgd(data->rb_arena, COLOR_PAIR(7));
	cmd_(data);
	wrefresh(data->rb_arena);
	data->r_arena = newwin(64, 66, 2, 205);
	wbkgd(data->r_arena, COLOR_PAIR(7));
	wbkgd(data->b_arena, COLOR_PAIR(7));
	vm_logoput(data);
	vm_init_sdl(data);
	data->pause = 1;
	data->ready = 0;
	data->sleep = -7;
	data->mode = 1;
	data->mode_death = 0;
	data->step = 0;
}
