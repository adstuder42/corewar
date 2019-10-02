/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:00:02 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:00:03 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	get_val(long int *value1, long int *value2
		, t_data *data, t_process *process)
{
	if (data->oct_c[0] == REG_CODE)
		*value1 = process->reg[data->param_val[0] - 1];
	if (data->oct_c[0] == DIR_CODE)
		*value1 = data->param_val[0];
	if (data->oct_c[0] == IND_CODE)
	{
		*value1 = mem_shift(data->param_val[0], process->pc, 0);
		*value1 = get_from_mem(*value1, REG_SIZE, data->arena);
	}
	if (data->oct_c[1] == REG_CODE)
		*value2 = process->reg[data->param_val[1] - 1];
	if (data->oct_c[1] == DIR_CODE)
		*value2 = data->param_val[1];
	if (data->oct_c[1] == IND_CODE)
	{
		*value2 = mem_shift(data->param_val[1], process->pc, 0);
		*value2 = get_from_mem(*value2, REG_SIZE, data->arena);
	}
}

int		and_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int		value1;
	long int		value2;

	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	get_val(&value1, &value2, data, process);
	process->reg[data->param_val[2] - 1] = value1 & value2;
	if (process->reg[data->param_val[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int		or_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int		value1;
	long int		value2;

	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	get_val(&value1, &value2, data, process);
	process->reg[data->param_val[2] - 1] = value1 | value2;
	if (process->reg[data->param_val[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int		xor_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int		value1;
	long int		value2;

	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	get_val(&value1, &value2, data, process);
	process->reg[data->param_val[2] - 1] = value1 ^ value2;
	if (process->reg[data->param_val[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}
