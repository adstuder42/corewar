/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncoded_instruct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 05:23:40 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 07:23:18 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int	noop(t_process *process, t_data *data, t_player *player, int cycle)
{
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (0);
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}
