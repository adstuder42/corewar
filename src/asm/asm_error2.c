/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:29:11 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 19:27:55 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_handle_error3(t_data *data, char *msg)
{
	t_asm_err	asm_errno;

	if (!(asm_errno.msg = ft_strdup(msg)))
		asm_memerr(data);
	asm_free_header(data->raw_header);
	ft_printf("Error : %s\n", asm_errno.msg);
	free(asm_errno.msg);
	exit(EXIT_FAILURE);
}

void	asm_handle_error4(t_data *data, int type, char *lab)
{
	if (type == dir_lab_exp)
		ft_printf("Error : %s %s %s%s\n", "No such label", lab,
			"while attempting to dereference token DIRECT_LABEL :", lab);
	else if (type == ind_lab_exp)
		ft_printf("Error : %s %s %s%s\n", "No such label", lab,
		"while attempting to dereference token INDIRECT_LABEL :", lab);
	asm_free_header(data->raw_header);
	asm_free_insts(data->first_inst);
	exit(EXIT_FAILURE);
}

void	asm_memerr(t_data *data)
{
	ft_printf("Malloc Error :(\n");
	asm_free_header(data->raw_header);
	asm_free_insts(data->first_inst);
	exit(EXIT_FAILURE);
}

void	asm_memerr2(t_data *data)
{
	ft_printf("Malloc Error :(\n");
	asm_free_header(data->raw_header);
	asm_free_insts(data->first_inst);
	free_label_calls(data->label_call);
	exit(EXIT_FAILURE);
}

void	asm_err(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
