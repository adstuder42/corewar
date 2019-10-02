/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check_instr_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:59:14 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 19:59:15 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int		vm_and_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 3 || data->oct_c[2] != REG_CODE)
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

int		vm_or_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 3 || data->oct_c[2] != REG_CODE)
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

int		vm_xor_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 3 || data->oct_c[2] != REG_CODE)
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

int		vm_zjmp_check(t_data *data, int addr, int oct_c, int nb_params)
{
	return (0);
	(void)data;
	(void)addr;
	(void)oct_c;
	(void)nb_params;
}
