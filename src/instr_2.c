/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:32:08 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 20:00:26 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int	ld_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int	ind_addr;

	process->carry = 0;
	ind_addr = 0;
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (data->oct_c[0] == DIR_CODE)
		process->reg[data->param_val[1] - 1] = data->param_val[0];
	if (data->oct_c[0] == IND_CODE)
	{
		ind_addr = mem_shift(data->param_val[0], process->pc, 0);
		process->reg[data->param_val[1] - 1] = get_from_mem(ind_addr
				, REG_SIZE, data->arena);
	}
	if (process->reg[data->param_val[1] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int	add_(t_process *process, t_data *data, t_player *player, int cycle)
{
	process->carry = 0;
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	process->reg[data->param_val[2] - 1] = process->reg[data->param_val[1] - 1]
		+ process->reg[data->param_val[0] - 1];
	if (process->reg[data->param_val[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int	lld_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int	ind_addr;

	process->carry = 0;
	ind_addr = 0;
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (data->oct_c[0] == DIR_CODE)
		process->reg[data->param_val[1] - 1] = data->param_val[0];
	if (data->oct_c[0] == IND_CODE)
	{
		ind_addr = mem_shift(data->param_val[0], process->pc, 1);
		process->reg[data->param_val[1] - 1] = get_from_mem(ind_addr, 2
				, data->arena);
	}
	if (process->reg[data->param_val[1] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int	lfork_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int		shift;
	int				i;

	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	shift = mem_shift(data->param_val[0], process->pc, 1);
	data->init_process[process->player_master] = create_process(
			data->init_process[process->player_master]
				, shift, process->player_master, data);
	i = 0;
	while (i < 16)
	{
		data->init_process[process->player_master]->reg[i] = process->reg[i];
		i++;
	}
	if (data->vis && player->first_fork && data->music.fork)
		Mix_PlayMusic(data->music.fork, 1);
	if (player->first_fork == 1)
		player->first_fork = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int	fork_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int		shift;
	int				i;

	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	shift = mem_shift(data->param_val[0], process->pc, 0);
	data->init_process[process->player_master] = create_process(
			data->init_process[process->player_master]
				, shift, process->player_master, data);
	i = 0;
	while (i < 16)
	{
		data->init_process[process->player_master]->reg[i] = process->reg[i];
		i++;
	}
	if (data->vis && player->first_fork && data->music.fork)
		Mix_PlayMusic(data->music.fork, 1);
	if (player->first_fork == 1)
		player->first_fork = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}
