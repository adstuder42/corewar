/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_insts2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:37:26 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:40:42 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_check_and(t_data *data, t_inst *inst, t_op *optab,
			t_asm_err asm_errno)
{
	if (inst->nbparams != 3)
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	if (inst->params[2].type != reg_exp)
	{
		asm_errno.paramnb = 2;
		asm_errno.type = inst->params[2].type;
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	}
}

void	asm_check_or(t_data *data, t_inst *inst, t_op *optab,
			t_asm_err asm_errno)
{
	if (inst->nbparams != 3)
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	if (inst->params[2].type != reg_exp)
	{
		asm_errno.paramnb = 2;
		asm_errno.type = inst->params[2].type;
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	}
}

void	asm_check_xor(t_data *data, t_inst *inst, t_op *optab,
			t_asm_err asm_errno)
{
	if (inst->nbparams != 3)
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	if (inst->params[2].type != reg_exp)
	{
		asm_errno.paramnb = 2;
		asm_errno.type = inst->params[2].type;
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	}
}

void	asm_check_zjmp(t_data *data, t_inst *inst, t_op *optab,
			t_asm_err asm_errno)
{
	if (inst->nbparams != 1)
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	if (inst->params[0].type != dir_int_exp
	&& inst->params[0].type != dir_lab_exp)
	{
		asm_errno.paramnb = 0;
		asm_errno.type = inst->params[0].type;
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	}
}
