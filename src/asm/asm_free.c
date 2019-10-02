/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:28:26 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:28:28 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_free_header(t_head *header)
{
	t_head	*tmp;

	while (header != NULL)
	{
		tmp = header->next;
		free(header);
		header = tmp;
	}
}

void	asm_free_params(t_inst *inst)
{
	int		i;

	i = 0;
	while (i < inst->nbparams)
	{
		if (inst->params[i].type == reg_exp)
			free(inst->params[i].val.reg.reg_exp);
		else if (inst->params[i].type == dir_lab_exp)
			free(inst->params[i].val.dir_lab);
		else if (inst->params[i].type == ind_lab_exp)
			free(inst->params[i].val.ind_lab);
		i++;
	}
}

void	asm_free_insts(t_inst *inst)
{
	t_inst	*tmp;
	int		i;

	while (inst != NULL)
	{
		tmp = inst->next;
		if (inst->label_bool)
		{
			if (inst->label)
			{
				i = 0;
				while (inst->label[i])
					free(inst->label[i++]);
				free(inst->label);
			}
		}
		asm_free_params(inst);
		free(inst);
		inst = tmp;
	}
}

void	free_label_calls(t_labcall *labcall)
{
	t_labcall	*tmp;

	while (labcall != NULL)
	{
		tmp = labcall->next;
		free(labcall->name);
		free(labcall);
		labcall = tmp;
	}
}

void	asm_free_label(char ***label)
{
	int		i;

	i = 0;
	while ((*label)[i])
	{
		free((*label)[i]);
		(*label)[i] = NULL;
		i++;
	}
	free(*label);
	*label = NULL;
}
