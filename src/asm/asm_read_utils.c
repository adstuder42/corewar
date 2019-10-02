/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:32:25 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:36:20 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_init_head(t_data *data, t_head **head)
{
	if (!(*head = (t_head *)malloc(sizeof(t_head))))
		asm_memerr(data);
	ft_bzero((*head)->val, sizeof((*head)->val));
	return (1);
}

int		asm_init_instruct(t_inst **inst)
{
	if (!(*inst = (t_inst *)malloc(sizeof(t_inst))))
		return (0);
	(*inst)->nbparams = 0;
	(*inst)->label = NULL;
	(*inst)->label_bool = 0;
	(*inst)->opc = 16;
	return (1);
}

void	asm_add_head(t_head **header, t_head *head)
{
	t_head	*first;

	if (*header == NULL)
	{
		head->next = NULL;
		*header = head;
		return ;
	}
	first = *header;
	while ((*header)->next != NULL)
		*header = (*header)->next;
	(*header)->next = head;
	head->next = NULL;
	*header = first;
}

void	asm_add_inst(t_data *data, t_inst **raw_inst, t_inst *inst,
			t_op *op_tab)
{
	t_inst	*first;

	if (inst->label_bool == 1 && inst->nbparams == 0)
		inst->label_bool = 2;
	asm_check(data, inst, op_tab);
	if (*raw_inst == NULL)
	{
		inst->next = NULL;
		*raw_inst = inst;
		return ;
	}
	first = *raw_inst;
	while ((*raw_inst)->next != NULL)
		*raw_inst = (*raw_inst)->next;
	(*raw_inst)->next = inst;
	inst->next = NULL;
	*raw_inst = first;
}

void	asm_init_dir_types(int *dir_types)
{
	dir_types[0] = T_INT;
	dir_types[1] = T_INT;
	dir_types[2] = T_NO;
	dir_types[3] = T_NO;
	dir_types[4] = T_NO;
	dir_types[5] = T_INT;
	dir_types[6] = T_INT;
	dir_types[7] = T_INT;
	dir_types[8] = T_SHORT;
	dir_types[9] = T_SHORT;
	dir_types[10] = T_SHORT;
	dir_types[11] = T_SHORT;
	dir_types[12] = T_INT;
	dir_types[13] = T_SHORT;
	dir_types[14] = T_SHORT;
	dir_types[15] = T_NO;
}
