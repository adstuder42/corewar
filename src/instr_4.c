/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:33:21 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 00:38:03 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int	ldi_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int	val1;
	long int	val2;

	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (data->oct_c[0] == IND_CODE)
	{
		val1 = mem_shift(data->param_val[0], process->pc, 0);
		val1 = get_from_mem(val1, REG_SIZE, data->arena);
	}
	if (data->oct_c[0] == DIR_CODE)
		val1 = data->param_val[0];
	if (data->oct_c[0] == REG_CODE)
		val1 = process->reg[data->param_val[0] - 1];
	if (data->oct_c[1] == DIR_CODE)
		val2 = data->param_val[1];
	if (data->oct_c[1] == REG_CODE)
		val2 = process->reg[data->param_val[1] - 1];
	process->reg[data->param_val[2] - 1] = get_from_mem(mem_shift((val1 + val2)
				, process->pc, 0), REG_SIZE, data->arena);
	process->carry = (process->reg[data->param_val[2] - 1]) ? 1 : 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int	lldi_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int	val1;
	long int	val2;

	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (data->oct_c[0] == IND_CODE)
	{
		val1 = mem_shift(data->param_val[0], process->pc, 1);
		val1 = get_from_mem(val1, REG_SIZE, data->arena);
	}
	if (data->oct_c[0] == DIR_CODE)
		val1 = data->param_val[0];
	if (data->oct_c[0] == REG_CODE)
		val1 = process->reg[data->param_val[0] - 1];
	if (data->oct_c[1] == DIR_CODE)
		val2 = data->param_val[1];
	if (data->oct_c[1] == REG_CODE)
		val2 = process->reg[data->param_val[1] - 1];
	process->reg[data->param_val[2] - 1] = get_from_mem(mem_shift((val1 + val2)
				, process->pc, 1), REG_SIZE, data->arena);
	process->carry = (process->reg[data->param_val[2] - 1]) ? 1 : 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int	aff_(t_process *process, t_data *data, t_player *player, int cycle)
{
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (data->vis)
		wprintw(data->b_arena, "Aff: %c\n"
				, process->reg[data->param_val[0] - 1] % 256);
	else
		ft_printf("Aff: %c\n", process->reg[data->param_val[0] - 1] % 256);
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int	sub_(t_process *process, t_data *data, t_player *player, int cycle)
{
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	process->reg[data->param_val[2] - 1] = process->reg[
		data->param_val[0] - 1] - process->reg[data->param_val[1] - 1];
	if (process->reg[data->param_val[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}
