/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check_instr_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:59:27 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 19:59:28 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int		vm_lfork_check(t_data *data, int addr, int oct_c, int nb_params)
{
	return (0);
	(void)data;
	(void)addr;
	(void)oct_c;
	(void)nb_params;
}

int		vm_aff_check(t_data *data, int addr, int oct_c, int nb_params)
{
	if (nb_params != 1 || data->oct_c[0] != REG_CODE)
	{
		data->next_inst_addr = mem_shift(addr + 2, 0, 1);
		return (1);
	}
	if (data->param_val[0] < 1 || data->param_val[0] > 16)
	{
		data->next_inst_addr = mem_shift(addr + nb_params + oct_c, 0, 1);
		return (1);
	}
	return (0);
	(void)oct_c;
}

int		vm_noop_check(t_data *data, int addr, int oct_c, int nb_params)
{
	return (0);
	(void)data;
	(void)addr;
	(void)oct_c;
	(void)nb_params;
}
