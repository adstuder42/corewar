/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check_instr_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:59:20 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 19:59:21 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int		vm_ldi_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 3
	|| data->oct_c[1] == IND_CODE
	|| data->oct_c[2] != REG_CODE)
	{
		data->next_inst_addr = mem_shift(addr + 2, 0, 1);
		return (1);
	}
	if ((data->oct_c[0] == REG_CODE
	&& (data->param_val[0] < 1 || data->param_val[0] > 16))
	|| (data->oct_c[1] == REG_CODE
	&& (data->param_val[1] < 1 || data->param_val[1] > 16))
	|| (data->param_val[2] < 1 || data->param_val[2] > 16))
	{
		data->next_inst_addr = mem_shift(addr + nb_params + oct_c, 0, 1);
		return (1);
	}
	return (0);
	(void)oct_c;
}

int		vm_sti_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 3
	|| data->oct_c[0] != REG_CODE
	|| data->oct_c[2] == IND_CODE)
	{
		data->next_inst_addr = mem_shift(addr + 2, 0, 1);
		return (1);
	}
	if ((data->param_val[0] < 1 || data->param_val[0] > 16)
	|| (data->oct_c[1] == REG_CODE
	&& (data->param_val[1] < 1 || data->param_val[1] > 16))
	|| (data->oct_c[2] == REG_CODE
	&& (data->param_val[2] < 1 || data->param_val[2] > 16)))
	{
		data->next_inst_addr = mem_shift(addr + nb_params + oct_c, 0, 1);
		return (1);
	}
	return (0);
	(void)oct_c;
}

int		vm_fork_check(t_data *data, int addr, int oct_c, int nb_params)
{
	return (0);
	(void)data;
	(void)addr;
	(void)oct_c;
	(void)nb_params;
}

int		vm_lld_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 2
	|| data->oct_c[0] == REG_CODE
	|| data->oct_c[1] != REG_CODE)
	{
		data->next_inst_addr = mem_shift(addr + 2, 0, 1);
		return (1);
	}
	if (data->param_val[1] < 1 || data->param_val[1] > 16)
	{
		data->next_inst_addr = mem_shift(addr + nb_params + oct_c, 0, 1);
		return (1);
	}
	return (0);
	(void)oct_c;
}

int		vm_lldi_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 3
	|| data->oct_c[1] == IND_CODE
	|| data->oct_c[2] != REG_CODE)
	{
		data->next_inst_addr = mem_shift(addr + 2, 0, 1);
		return (1);
	}
	if ((data->oct_c[0] == REG_CODE
	&& (data->param_val[0] < 1 || data->param_val[0] > 16))
	|| (data->oct_c[1] == REG_CODE
	&& (data->param_val[1] < 1 || data->param_val[1] > 16))
	|| data->param_val[2] < 1 || data->param_val[2] > 16)
	{
		data->next_inst_addr = mem_shift(addr + nb_params + oct_c, 0, 1);
		return (1);
	}
	return (0);
	(void)oct_c;
}
