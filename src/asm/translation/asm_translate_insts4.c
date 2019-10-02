/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate_insts4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:38 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:38:39 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_lfork(t_data *data, t_inst *inst, unsigned char *corfile,
			t_op *op_tab)
{
	inst->address = data->nb_bytes;
	asm_cor_memcpy1(data, corfile, 1, (unsigned char)op_tab[inst->opc].opnum);
	asm_dir_param(data, inst, corfile, 0);
}

void	asm_aff(t_data *data, t_inst *inst, unsigned char *corfile,
			t_op *op_tab)
{
	inst->address = data->nb_bytes;
	asm_cor_memcpy1(data, corfile, 1, (unsigned char)op_tab[inst->opc].opnum);
	asm_cor_memcpy1(data, corfile, 1, (unsigned char)0x40);
	asm_cor_uintcpy(data, corfile, inst->params[0].val.reg.value, 1);
}

void	asm_null(t_data *data, t_inst *inst, unsigned char *corfile,
			t_op *op_tab)
{
	inst->address = data->nb_bytes;
	(void)corfile;
	(void)op_tab;
}
