/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate_insts2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:28 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:38:29 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_and(t_data *data, t_inst *inst, unsigned char *corfile,
			t_op *op_tab)
{
	inst->address = data->nb_bytes;
	asm_cor_memcpy1(data, corfile, 1, (unsigned char)op_tab[inst->opc].opnum);
	asm_paramcode(data, inst, corfile);
	if (inst->params[0].type == reg_exp)
		asm_cor_uintcpy(data, corfile, inst->params[0].val.reg.value, 1);
	else if (inst->params[0].type == dir_int_exp
	|| inst->params[0].type == dir_lab_exp)
		asm_dir_param(data, inst, corfile, 0);
	else if (inst->params[0].type == ind_int_exp
	|| inst->params[0].type == ind_lab_exp)
		asm_undir_param(data, inst, corfile, 0);
	if (inst->params[1].type == reg_exp)
		asm_cor_uintcpy(data, corfile, inst->params[1].val.reg.value, 1);
	else if (inst->params[1].type == dir_int_exp
	|| inst->params[1].type == dir_lab_exp)
		asm_dir_param(data, inst, corfile, 1);
	else if (inst->params[1].type == ind_int_exp
	|| inst->params[1].type == ind_lab_exp)
		asm_undir_param(data, inst, corfile, 1);
	asm_cor_uintcpy(data, corfile, inst->params[2].val.reg.value, 1);
}

void	asm_or(t_data *data, t_inst *inst, unsigned char *corfile,
			t_op *op_tab)
{
	inst->address = data->nb_bytes;
	asm_cor_memcpy1(data, corfile, 1, (unsigned char)op_tab[inst->opc].opnum);
	asm_paramcode(data, inst, corfile);
	if (inst->params[0].type == reg_exp)
		asm_cor_uintcpy(data, corfile, inst->params[0].val.reg.value, 1);
	else if (inst->params[0].type == dir_int_exp
	|| inst->params[0].type == dir_lab_exp)
		asm_dir_param(data, inst, corfile, 0);
	else if (inst->params[0].type == ind_int_exp
	|| inst->params[0].type == ind_lab_exp)
		asm_undir_param(data, inst, corfile, 0);
	if (inst->params[1].type == reg_exp)
		asm_cor_uintcpy(data, corfile, inst->params[1].val.reg.value, 1);
	else if (inst->params[1].type == dir_int_exp
	|| inst->params[1].type == dir_lab_exp)
		asm_dir_param(data, inst, corfile, 1);
	else if (inst->params[1].type == ind_int_exp
	|| inst->params[1].type == ind_lab_exp)
		asm_undir_param(data, inst, corfile, 1);
	asm_cor_uintcpy(data, corfile, inst->params[2].val.reg.value, 1);
}

void	asm_xor(t_data *data, t_inst *inst, unsigned char *corfile,
			t_op *op_tab)
{
	inst->address = data->nb_bytes;
	asm_cor_memcpy1(data, corfile, 1, (unsigned char)op_tab[inst->opc].opnum);
	asm_paramcode(data, inst, corfile);
	if (inst->params[0].type == reg_exp)
		asm_cor_uintcpy(data, corfile, inst->params[0].val.reg.value, 1);
	else if (inst->params[0].type == dir_int_exp
	|| inst->params[0].type == dir_lab_exp)
		asm_dir_param(data, inst, corfile, 0);
	else if (inst->params[0].type == ind_int_exp
	|| inst->params[0].type == ind_lab_exp)
		asm_undir_param(data, inst, corfile, 0);
	if (inst->params[1].type == reg_exp)
		asm_cor_uintcpy(data, corfile, inst->params[1].val.reg.value, 1);
	else if (inst->params[1].type == dir_int_exp
	|| inst->params[1].type == dir_lab_exp)
		asm_dir_param(data, inst, corfile, 1);
	else if (inst->params[1].type == ind_int_exp
	|| inst->params[1].type == ind_lab_exp)
		asm_undir_param(data, inst, corfile, 1);
	asm_cor_uintcpy(data, corfile, inst->params[2].val.reg.value, 1);
}

void	asm_zjmp(t_data *data, t_inst *inst, unsigned char *corfile,
			t_op *op_tab)
{
	inst->address = data->nb_bytes;
	asm_cor_memcpy1(data, corfile, 1, (unsigned char)op_tab[inst->opc].opnum);
	asm_dir_param(data, inst, corfile, 0);
}
