/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_reaper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 02:19:37 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 02:20:50 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int	kill_every_one(t_player *player, t_data *data)
{
	int			i;
	t_process	*process_tmp;

	i = 0;
	while (i < data->nbr_of_players)
	{
		(player + i)->process = data->init_process[i];
		while ((player + i)->process)
		{
			process_tmp = (player + i)->process->next;
			free((player + i)->process);
			(player + i)->process = process_tmp;
		}
		i++;
	}
	return (0);
}
