/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_insts4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:37:36 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:37:37 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_check_lfork(t_data *data, t_inst *inst, t_op *optab,
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

void	asm_check_aff(t_data *data, t_inst *inst, t_op *optab,
			t_asm_err asm_errno)
{
	if (inst->nbparams != 1)
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	if (inst->params[0].type != reg_exp)
	{
		asm_errno.paramnb = 0;
		asm_errno.type = inst->params[0].type;
		asm_handle_error2(data, asm_errno, inst->opc, optab);
	}
}

void	asm_check_null(t_data *data, t_inst *inst, t_op *optab,
			t_asm_err asm_errno)
{
	(void)data;
	(void)inst;
	(void)optab;
	(void)asm_errno;
}
