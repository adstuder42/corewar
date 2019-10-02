/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 13:31:38 by adstuder          #+#    #+#             */
/*   Updated: 2019/09/21 13:33:21 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	reset_live_count(t_data *data, t_player *player, int players_nbr)
{
	int i;

	i = 0;
	while (i < players_nbr)
	{
		(player + i)->live_count = 0;
		set_aliveprocess(data, i, 0);
		i++;
	}
}

int		check_life_process(t_data *data, int i)
{
	t_process	*process;

	process = data->init_process[i];
	while (process)
	{
		if (process->alive == 1)
			return (1);
		process = process->next;
	}
	return (0);
}

void	kill_player(t_data *data, t_player *player, int i)
{
	char	*name;
	int		num;

	name = (player + i)->name;
	num = (player + i)->num;
	(player + i)->alive = 0;
	(player + i)->live_count = 0;
	data->alive_players--;
	if (data->vis)
		wprintw(data->b_arena, "Player %s (%d) is DEAD\n", name, num);
	else if (!data->vis)
		ft_printf("Player %s(%d) is DEAD\n", name, num);
	if (data->vis && data->music.death && data->alive_players != 0)
		Mix_PlayMusic(data->music.death, 1);
}

int		check_life(t_data *data, t_player *player, int live_count, int i)
{
	if ((player + i)->live_count <= 0 && (player + i)->alive == 1)
	{
		if (check_life_process(data, i) == 0)
			kill_player(data, player, i);
	}
	else if ((player + i)->live_count > 0 && (player + i)->alive == 1)
		live_count = live_count + (player + i)->live_count;
	vm_process_die(data, i);
	return (live_count);
}

int		live_checker(t_data *data, t_player *player)
{
	int i;
	int live_count;

	i = data->nbr_of_players;
	live_count = 0;
	player = data->player_0;
	if (data->vis)
		werase(data->b_arena);
	while (i-- > 0)
		live_count = check_life(data, player, live_count, i);
	live_count = live_count + data->nb_process_lives;
	if (data->vis)
		wrefresh(data->b_arena);
	data->max_checks--;
	if (live_count >= NBR_LIVE || data->max_checks <= 0)
		data->cycle_to_die_tmp = data->cycle_to_die_tmp - CYCLE_DELTA;
	if (live_count >= NBR_LIVE || data->max_checks <= 0)
		data->max_checks = MAX_CHECKS;
	if (data->cycle_to_die_tmp <= 0)
		data->cycle_to_die_tmp = 1;
	if (data->alive_players <= 0)
		return (display_winner(data, player, data->nbr_of_players));
	data->live_checker_countdown = data->cycle_to_die_tmp;
	reset_live_count(data, player, data->nbr_of_players);
	return (0);
}
