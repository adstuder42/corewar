/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:22:57 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:30:00 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_free_ex(t_asm_err asm_errno)
{
	free(asm_errno.msg2);
	free(asm_errno.typemsg);
	asm_memerr3();
}

void	asm_handle_error21(t_asm_err *asm_errno)
{
	if (asm_errno->type == reg_exp)
	{
		if (!(asm_errno->typemsg2 = ft_strdup("register")))
			asm_free_ex(*asm_errno);
	}
	else if (asm_errno->type == dir_int_exp
		|| asm_errno->type == dir_lab_exp)
	{
		if (!(asm_errno->typemsg2 = ft_strdup("direct")))
			asm_free_ex(*asm_errno);
	}
	else if (asm_errno->type == ind_int_exp
	|| asm_errno->type == ind_lab_exp)
	{
		if (!(asm_errno->typemsg2 = ft_strdup("indirect")))
			asm_free_ex(*asm_errno);
	}
}

void	asm_memerr3(void)
{
	ft_printf("Malloc Error :(\n");
	exit(EXIT_FAILURE);
}
