/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 03:49:57 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 20:33:26 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int			prepare_the_war(t_data *data, t_player *player)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_players)
	{
		(player + i)->alive = 1;
		(player + i)->process = NULL;
		(player + i)->first_fork = 1;
		if (!((player + i)->process = create_process((player + i)->process
						, (player + i)->pos, i, data)))
			return (0);
		(player + i)->process->reg[0] = (player + i)->num;
		data->init_process[i] = (player + i)->process;
		i++;
	}
	return (1);
}

int			prepare_instr_exec(t_player *player, t_data *data
		, int *actual_process_instruction, const int instruction_nbr_cycle[])
{
	*actual_process_instruction = data->arena[player->process->pc];
	if (*actual_process_instruction > 16)
	{
		data->p_arena[player->process->pc] = 0;
		player->process->pc = mem_shift(1, player->process->pc, 1);
		data->p_arena[player->process->pc] = 1;
		player->process = player->process->next;
		return (0);
	}
	if (!player->process->activation_countdown)
	{
		data->c_dump = 1;
		data->p_arena[player->process->pc] = 1;
		player->process->activation_countdown =
			instruction_nbr_cycle[*actual_process_instruction];
	}
	else
		player->process->activation_countdown--;
	return (1);
}

int			browse_process(t_player *player, t_data *data, int cycle)
{
	int			actual_process_instruction;
	static	int	(*ins[17])(t_process *, t_data *, t_player *, int) = {noop, live
		, ld_, st_, add_, sub_, and_, or_, xor_, zjump_, ldi_
			, sti_, fork_, lld_, lldi_, lfork_, aff_};
	const	int	instruction_nbr_cycle[17] = { 0, 10, 5, 5, 10, 10, 6,
		6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

	while (player->process)
	{
		if (!prepare_instr_exec(player, data, &actual_process_instruction
					, instruction_nbr_cycle))
			continue;
		if (!player->process->activation_countdown)
		{
			data->p_arena[player->process->pc] = 0;
			player->process->pc = ins[actual_process_instruction](
					player->process, data, player, cycle);
			data->p_arena[player->process->pc] = 1;
		}
		player->process = player->process->next;
	}
	return (1);
}

int			battle(t_data *data, t_player *players, int *cycle)
{
	int	i;

	vm_ncur_before_fight(data, *cycle, players);
	if (data->live_checker_countdown == 0)
		if (live_checker(data, players) != 0)
			return (0);
	i = data->nbr_of_players;
	while (i-- > 0)
		if ((players + i)->alive)
		{
			(players + i)->process = data->init_process[i];
			if (!browse_process(players + i, data, *cycle))
				return (0);
		}
	data->live_checker_countdown--;
	vm_ncur_after_fight(data, *cycle, players);
	return (1);
}

int			war_time(t_data *data, t_player *players)
{
	int		cycle;

	cycle = 0;
	data->c_dump = 1;
	if (!prepare_the_war(data, players))
		return (0);
	init_uninitialized(data, players);
	data->player_0 = players;
	while (1)
	{
		if (!battle(data, players, &cycle))
			break ;
		if (cycle == data->nbr_cycles && (!data->vis))
		{
			mem_dump(data->arena);
			break ;
		}
		cycle++;
	}
	(data->vis) ? vm_ncurs_end(data, cycle, players) : 0;
	(data->nbr_cycles == -42) ? ft_printf("War over!\n") : 0;
	return (1);
}
