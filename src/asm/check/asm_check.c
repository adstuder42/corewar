/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:37:45 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:04:45 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_check(t_data *data, t_inst *inst, t_op *op_tab)
{
	t_asm_err	asm_errno;
	static void	(*f[17])(t_data *, t_inst *, t_op *, t_asm_err) = {
		asm_check_live, asm_check_ld, asm_check_st, asm_check_add,
		asm_check_sub, asm_check_and, asm_check_or, asm_check_xor,
		asm_check_zjmp, asm_check_ldi, asm_check_sti, asm_check_fork,
		asm_check_lld, asm_check_lldi, asm_check_lfork,
		asm_check_aff, asm_check_null};

	if (!(asm_errno.msg = ft_strdup("Invalid parameter")))
		asm_memerr(data);
	if (!(asm_errno.endmsg = ft_strdup("for instruction")))
	{
		free(asm_errno.msg);
		asm_memerr(data);
	}
	asm_errno.paramnb = -1;
	f[inst->opc](data, inst, op_tab, asm_errno);
	free(asm_errno.msg);
	free(asm_errno.endmsg);
}
