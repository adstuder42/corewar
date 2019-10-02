/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 13:31:26 by adstuder          #+#    #+#             */
/*   Updated: 2019/09/21 13:40:52 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	write_reg(t_data *data, int addr, int nb, int player_nb)
{
	int i;
	int	shift;

	shift = 24;
	i = 0;
	while (i < REG_SIZE)
	{
		data->arena[addr] = (nb >> shift) & 0xff;
		data->c_arena[addr] = player_nb + 1;
		addr = mem_shift(addr + 1, 0, 1);
		shift -= 8;
		i++;
	}
}

int		st_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int	ind_addr;

	ind_addr = 0;
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (data->oct_c[1] == REG_CODE)
		process->reg[data->param_val[1] - 1] =
		process->reg[data->param_val[0] - 1];
	if (data->oct_c[1] == IND_CODE)
	{
		ind_addr = mem_shift(data->param_val[1], process->pc, 0);
		write_reg(data, ind_addr, process->reg[data->param_val[0] - 1],
			process->player_master);
	}
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int		sti_(t_process *process, t_data *data, t_player *player, int cycle)
{
	long int	ind_addr1;
	long int	ind_addr2;

	ind_addr1 = 0;
	ind_addr2 = 0;
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (data->oct_c[1] == IND_CODE)
		ind_addr1 = mem_shift(data->param_val[1], process->pc, 0);
	if (data->oct_c[1] == IND_CODE)
		ind_addr1 = get_from_mem(ind_addr1, REG_SIZE, data->arena);
	else if (data->oct_c[1] == DIR_CODE)
		ind_addr1 = data->param_val[1];
	else
		ind_addr1 = process->reg[data->param_val[1] - 1];
	if (data->oct_c[2] == REG_CODE)
		ind_addr2 = process->reg[data->param_val[2] - 1];
	else
		ind_addr2 = data->param_val[2];
	ind_addr1 = mem_shift((ind_addr1 + ind_addr2), process->pc, 0);
	write_reg(data, ind_addr1, process->reg[data->param_val[0] - 1],
		process->player_master);
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}

int		zjump_(t_process *process, t_data *data, t_player *player, int cycle)
{
	if (!parsing_ins(data, process->pc + 1, data->arena[process->pc]))
		return (data->next_inst_addr);
	if (process->carry == 1)
		return (mem_shift(data->param_val[0], process->pc, 0));
	return (data->next_inst_addr);
	(void)cycle;
	(void)player;
}
