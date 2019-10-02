/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:20:49 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/18 20:59:23 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "../inc/vm.h"

int		asm_err(int i, int buf)
{
	const	int	magic[4] = {0, 234, 131, 243};

	if (i < 4 && magic[i] != buf)
	{
		ft_printf("\nThis is not good corewar file\nsorry :-(\n");
		return (1);
	}
	return (0);
}

int		extract_instruct(int buf, int players_nbr
		, t_data *data, t_player *player)
{
	static	int	player_n = -42;
	static	int	i;
	static	int	j = 0;
	static	int	player_order = 0;

	if ((player_n) != player->num)
	{
		i = 0;
		player_order++;
		player_n = player->num;
		player->pos = (player_order - 1) * (MEM_SIZE / players_nbr);
	}
	j = player->pos + i;
	data->arena[j] = buf;
	data->c_arena[j] = player_order;
	i++;
	return (1);
}

void	get_champion_data(int i, int buf, t_player *player)
{
	static	int	i_ = 0;

	if (i >= 4 && i < (PROG_NAME_LENGTH + 4))
	{
		player->name[i_] = (char)buf;
		i_++;
	}
	else if (i >= 132 + 8 && i < (4 + PROG_NAME_LENGTH + COMMENT_LENGTH))
	{
		player->comment[i_] = (char)buf;
		i_++;
	}
	else if (i >= 132 + 4 && i < 140)
	{
		i_ = 0;
		if (i == 136)
			player->prog_size_head = 0;
		player->prog_size_head += buf;
		if (i != 139)
			player->prog_size_head = player->prog_size_head << 8;
		else if (player->prog_size_head > CHAMP_MAX_SIZE)
			vm_err_player("Program size too large for player", player->name);
	}
	else
		i_ = 0;
}

int		parse_asm_arg(char *argv, t_player *player
		, t_data *data, int players_nbr)
{
	int	fd;
	int	buffer;
	int	i;

	i = 0;
	buffer = 0;
	fd = 0;
	fd = open(argv, O_RDWR);
	while (read(fd, &buffer, 1) > 0)
	{
		if (asm_err(i, buffer))
			return (0);
		get_champion_data(i, buffer, player);
		if (i >= (4 + 8 + 4 + PROG_NAME_LENGTH + COMMENT_LENGTH))
			if (!extract_instruct(buffer, players_nbr, data, player))
				return (0);
		i++;
	}
	return (check_prog_size(player, i, argv));
}

int		main(int argc, char **argv)
{
	t_player	players[MAX_PLAYERS];
	t_data		data[1];

	data->parsing_state = DEFAULT_STATE;
	data->nbr_of_players = 0;
	data->nbr_cycles = -42;
	data->vis = 0;
	ft_bzero(data->c_arena, sizeof(data->c_arena));
	ft_bzero(data->p_arena, sizeof(data->p_arena));
	ft_bzero(data->arena, sizeof(data->arena));
	ft_bzero(data->assigned_player_nums, sizeof(data->assigned_player_nums));
	if (!parsing(argv, argc, data, players))
		return (0);
	if (data->nbr_of_players < 1 || data->nbr_of_players > 4)
		return (err("number of players must be bewin 2 and 4"));
	if (data->vis)
		vm_init_ncurses(data);
	war_time(data, players);
	kill_every_one(players, data);
	return (0);
}
