/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_manager_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 13:33:54 by adstuder          #+#    #+#             */
/*   Updated: 2019/09/21 13:35:38 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int		live(t_process *process, t_data *data, t_player *player, int cycle)
{
	int		id;
	int		i;
	char	*txt;

	id = data->param_val[0];
	i = 0;
	txt = "un processus dit que le joueur %d(%s) est en vie\n";
	player = data->player_0;
	process->alive = 1;
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	while (i < data->nbr_of_players && (player + i)->num != id)
		i++;
	if (i >= data->nbr_of_players || (player + i)->alive == 0)
		data->nb_process_lives++;
	if (i >= data->nbr_of_players || (player + i)->alive == 0)
		return (data->next_inst_addr);
	(player + i)->live_count++;
	data->last_live = (player + i)->num;
	if (data->vis)
		wprintw(data->b_arena, txt, (player + i)->num, (player + i)->name);
	else if (data->vis == 0 && (data->nbr_cycles == -42
	|| data->nbr_cycles == cycle))
		ft_printf(txt, (player + i)->num, (player + i)->name);
	return (data->next_inst_addr);
}

void	init_uninitialized(t_data *data, t_player *player)
{
	int i;

	i = 0;
	while (i < data->nbr_of_players)
	{
		(player + i)->live_count = 0;
		(player + i)->alive = 1;
		i++;
	}
	data->nb_process_lives = 0;
	data->cycle_to_die_tmp = CYCLE_TO_DIE;
	data->live_checker_countdown = data->cycle_to_die_tmp;
	data->alive_players = data->nbr_of_players;
	data->last_live = (player->num);
	data->max_checks = MAX_CHECKS;
}

int		display_winner(t_data *data, t_player *player, int nbr_of_players)
{
	int		i;
	int		last_live;
	char	*txt;

	i = 0;
	txt = "le joueur %d(%s) a gagne\n";
	last_live = data->last_live;
	player = data->player_0;
	while (i < nbr_of_players && last_live != (player + i)->num)
		i++;
	if (data->vis)
		wprintw(data->b_arena, txt, last_live, (player + i)->name);
	else
		ft_printf(txt, last_live, (player + i)->name);
	return (1);
}
