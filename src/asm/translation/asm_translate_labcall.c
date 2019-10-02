/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate_labcall.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:42 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 02:39:59 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_init_labcall(t_data *data, t_labcall **labcall)
{
	if (!(*labcall = (t_labcall *)malloc(sizeof(t_labcall))))
		asm_memerr(data);
	return (1);
}

void	asm_write_lab(t_data *data, t_inst *inst, int *flag)
{
	int				i;
	unsigned int	nb;

	i = 0;
	while (inst->label && inst->label[i])
	{
		if (inst->label_bool == 1
		&& !ft_strcmp(inst->label[i], data->label_call->name))
		{
			nb = inst->address - data->label_call->address_inst;
			if (data->label_call->bytes == 4)
				asm_cor_uileeks(data, nb, data->label_call->addr_tow);
			else if (data->label_call->bytes == 2)
				asm_cor_usileeks(data, nb, data->label_call->addr_tow);
			*flag = 1;
			break ;
		}
		i++;
	}
}

void	asm_search_lab(t_data *data, t_inst *first)
{
	int			flag;
	t_inst		*inst;

	flag = 0;
	inst = first;
	while (inst != NULL)
	{
		asm_write_lab(data, inst, &flag);
		if (flag == 1)
			break ;
		inst = inst->next;
	}
}

void	asm_label_call(t_data *data)
{
	t_labcall	*first_lab;
	t_inst		*first;

	first = data->inst;
	first_lab = data->label_call;
	while (data->label_call != NULL)
	{
		asm_search_lab(data, first);
		data->label_call = data->label_call->next;
	}
	data->label_call = first_lab;
}
