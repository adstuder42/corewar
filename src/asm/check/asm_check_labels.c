/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_labels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:37:40 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:42:54 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_has_labelcall(t_inst *inst)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (i < inst->nbparams)
	{
		if (inst->params[i].type == dir_lab_exp
		|| inst->params[i].type == ind_lab_exp)
			len++;
		i++;
	}
	return (len);
}

int		asm_lab_exists(t_data *data, int i, t_inst *insts)
{
	int		j;

	j = 0;
	while (insts->label[j] != NULL)
	{
		if (data->inst->params[i].type == dir_lab_exp
		&& !ft_strcmp(insts->label[j], data->inst->params[i].val.dir_lab))
			return (1);
		if (data->inst->params[i].type == ind_lab_exp
		&& !ft_strcmp(insts->label[j], data->inst->params[i].val.ind_lab))
			return (1);
		j++;
	}
	return (0);
}

void	asm_browse_inst_lab(t_data *data, int i, t_inst *first)
{
	t_inst	*insts;
	int		exist;

	exist = FALSE;
	insts = first;
	while (insts != NULL)
	{
		if (insts->label_bool > 0)
		{
			exist = asm_lab_exists(data, i, insts);
		}
		if (exist)
			break ;
		insts = insts->next;
	}
	if (!exist && data->inst->params[i].type == dir_lab_exp)
		asm_handle_error4(data, dir_lab_exp, data->inst->params[i].val.dir_lab);
	else if (!exist && data->inst->params[i].type == ind_lab_exp)
		asm_handle_error4(data, ind_lab_exp, data->inst->params[i].val.ind_lab);
}

void	asm_check_labels(t_data *data)
{
	t_inst	*first;
	int		i;

	first = data->inst;
	while (data->inst != NULL)
	{
		if (asm_has_labelcall(data->inst))
		{
			i = 0;
			while (i < data->inst->nbparams)
			{
				if (data->inst->params[i].type == dir_lab_exp
				|| data->inst->params[i].type == ind_lab_exp)
					asm_browse_inst_lab(data, i, first);
				i++;
			}
		}
		data->inst = data->inst->next;
	}
	data->inst = first;
	if (data->inst == NULL)
		asm_handle_error3(data, "Nothing to write for program");
}
