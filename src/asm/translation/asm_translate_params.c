/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:47 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:09:26 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_labcall_create(t_data *data, t_inst *inst, t_labcall **label_call,
			int i)
{
	t_labcall	*first;

	first = data->label_call;
	asm_init_labcall(data, label_call);
	(*label_call)->addr_tow = data->nb_bytes;
	(*label_call)->address_inst = inst->address;
	if (!((*label_call)->name = ft_strdup(inst->params[i].val.dir_lab)))
	{
		data->label_call = first;
		free(*label_call);
		asm_memerr2(data);
	}
	(*label_call)->next = NULL;
	if (data->label_call != NULL)
	{
		while (data->label_call->next != NULL)
			data->label_call = data->label_call->next;
		data->label_call->next = *label_call;
		data->label_call = first;
	}
	else
		data->label_call = *label_call;
}

void	asm_dir_param(t_data *data, t_inst *inst, unsigned char *corfile,
			int i)
{
	t_labcall		*label_call;
	int				dir_types[16];

	asm_init_dir_types(dir_types);
	if (inst->params[i].type == dir_int_exp
	&& dir_types[inst->opc] == T_INT)
		asm_cor_uintcpy(data, corfile, inst->params[i].val.dir_int, 4);
	else if (inst->params[i].type == dir_int_exp
	&& dir_types[inst->opc] == T_SHORT)
		asm_cor_uintcpy(data, corfile, inst->params[i].val.dir_int, 2);
	else if (inst->params[i].type == dir_lab_exp)
	{
		asm_labcall_create(data, inst, &label_call, i);
		if (dir_types[inst->opc] == T_INT)
		{
			label_call->bytes = 4;
			asm_cor_uintcpy(data, corfile, 0, 4);
		}
		else if (dir_types[inst->opc] == T_SHORT)
		{
			label_call->bytes = 2;
			asm_cor_uintcpy(data, corfile, 0, 2);
		}
	}
}

void	asm_dup_lab(t_data *data, t_inst *inst, int i, t_labcall **label_call)
{
	if (!((*label_call)->name = ft_strdup(inst->params[i].val.ind_lab)))
	{
		free(*label_call);
		asm_memerr2(data);
	}
}

void	asm_undir_param(t_data *data, t_inst *inst, unsigned char *corfile,
			int i)
{
	t_labcall		*label_call;
	t_labcall		*first;

	first = data->label_call;
	if (inst->params[i].type == ind_int_exp)
		asm_cor_uintcpy(data, corfile, inst->params[i].val.ind_int, 2);
	else if (inst->params[i].type == ind_lab_exp)
	{
		asm_init_labcall(data, &label_call);
		label_call->addr_tow = data->nb_bytes;
		label_call->address_inst = inst->address;
		asm_dup_lab(data, inst, i, &label_call);
		label_call->next = NULL;
		if (data->label_call != NULL)
		{
			while (data->label_call->next != NULL)
				data->label_call = data->label_call->next;
			data->label_call->next = label_call;
			data->label_call = first;
		}
		else
			data->label_call = label_call;
		label_call->bytes = 2;
		asm_cor_uintcpy(data, corfile, 0, 2);
	}
}

void	asm_paramcode(t_data *data, t_inst *inst, unsigned char *corfile)
{
	unsigned int	byte;

	byte = 0;
	if (inst->params[0].type == reg_exp)
		byte |= 0x40;
	else if (inst->params[0].type == dir_int_exp
	|| inst->params[0].type == dir_lab_exp)
		byte |= 0x80;
	else if (inst->params[0].type == ind_int_exp
	|| inst->params[0].type == ind_lab_exp)
		byte |= 0xc0;
	if (inst->params[1].type == reg_exp)
		byte |= 0x10;
	else if (inst->params[1].type == dir_int_exp
	|| inst->params[1].type == dir_lab_exp)
		byte |= 0x20;
	else if (inst->params[1].type == ind_int_exp
	|| inst->params[1].type == ind_lab_exp)
		byte |= 0x30;
	if (inst->nbparams == 3 && inst->params[2].type == reg_exp)
		byte |= 0x4;
	else if (inst->nbparams == 3 && (inst->params[2].type == dir_int_exp
	|| inst->params[2].type == dir_lab_exp))
		byte |= 0x8;
	asm_cor_uintcpy(data, corfile, byte, 1);
}
