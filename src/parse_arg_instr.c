/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_instr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:57:49 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 18:28:08 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	def_val(t_data *data, int addr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < data->param_size[i])
		{
			data->param_val[i] += data->arena[addr];
			if (j != data->param_size[i] - 1)
				data->param_val[i] = data->param_val[i] << 8;
			addr++;
			j++;
		}
		i++;
	}
}

int		find_sizeof_non_oct_c_param(t_data *data, int *addr, int op_code)
{
	if (op_code == 1)
		data->param_size[0] = 4;
	else
		data->param_size[0] = 2;
	data->params_size = data->param_size[0];
	(*addr)--;
	return (1);
	(void)addr;
}

int		parse_val(t_data *data, int addr, int op_code)
{
	int			i;
	const	int	sze[17] = {0, 0, 4, 0, 0, 0, 4, 4, 4, 2, 2, 2, 2, 4, 2
		, 2, 0};

	i = 0;
	ft_bzero(data->param_size, sizeof(data->param_size));
	data->params_size = 0;
	if (data->oct_c[0])
	{
		while (i < 4)
		{
			if (data->oct_c[i] == REG_CODE)
				data->param_size[i] = 1;
			if (data->oct_c[i] == DIR_CODE)
				data->param_size[i] = sze[op_code];
			if (data->oct_c[i] == IND_CODE)
				data->param_size[i] = 2;
			data->params_size += data->param_size[i];
			i++;
		}
	}
	else
		find_sizeof_non_oct_c_param(data, &addr, op_code);
	def_val(data, addr);
	return (0);
}

int		parse_oct_c(t_data *data, int addr, int *nbp)
{
	int		i[2];
	char	oct_char[9];
	char	tmp[3];
	int		type;

	ft_itoa_base2(data->arena[addr], oct_char);
	ft_bzero(i, sizeof(i));
	ft_bzero(tmp, sizeof(tmp));
	*nbp = 0;
	while (oct_char[i[0]] && (i[1] < 2 || ft_strcmp(tmp, "00")))
	{
		if (i[1] == 2)
		{
			type = (!ft_strcmp(tmp, "01")) ? REG_CODE : type;
			type = (!ft_strcmp(tmp, "10")) ? DIR_CODE : type;
			type = (!ft_strcmp(tmp, "11")) ? IND_CODE : type;
			data->oct_c[*nbp] = type;
			(*nbp)++;
			i[1] = 0;
		}
		tmp[i[1]] = oct_char[i[0]];
		i[0]++;
		i[1]++;
	}
	return (*nbp);
}

int		parsing_ins(t_data *data, int addr, int op_code)
{
	const	int	oct_c[17] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};
	static	int	(*vm_ins_check[17])(t_data *, int, int, int) = {
		vm_noop_check, vm_live_check, vm_ld_check, vm_st_check,
		vm_add_check, vm_sub_check, vm_and_check, vm_or_check, vm_xor_check
			, vm_zjmp_check, vm_ldi_check, vm_sti_check, vm_fork_check
			, vm_lld_check, vm_lldi_check, vm_lfork_check, vm_aff_check};
	int			nb_params;

	ft_bzero(data->oct_c, sizeof(data->oct_c));
	ft_bzero(data->param_val, sizeof(data->param_val));
	ft_bzero(data->param_size, sizeof(data->param_size));
	nb_params = 0;
	if (oct_c[op_code])
		parse_oct_c(data, addr, &nb_params);
	addr++;
	parse_val(data, addr, op_code);
	if (!op_code)
		data->params_size = 0;
	addr -= 1;
	if (vm_ins_check[op_code](data, addr, oct_c[op_code], nb_params))
		return (0);
	else
		data->next_inst_addr = mem_shift(addr
				+ data->params_size + oct_c[op_code], 0, 1);
	return (1);
}
