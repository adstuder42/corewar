/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:07 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:51:55 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_parse_label(t_data *data, t_inst **inst, char *sline,
			int *i)
{
	i[2] = TRUE;
	if (*inst != NULL)
		asm_handle_error(data, i[0], i[1],
			"Syntax error, token type : LABEL ");
	asm_init_instruct(inst);
	if (!((*inst)->label = (char **)malloc(sizeof(char *) * 2)))
		asm_memerr(data);
	if (asm_is_label(sline) == 1)
	{
		if (!((*inst)->label[0] = ft_strndup(sline, ft_strlen(sline) - 1)))
			asm_memerr(data);
	}
	else
		asm_stuck_opcode(data, inst, sline, i);
	(*inst)->label[1] = NULL;
	(*inst)->label_bool = 1;
}

void	asm_parse_opcode(t_data *data, t_inst **inst, char *splited_line,
			int *i)
{
	int		j;

	i[2] = TRUE;
	if (*inst == NULL)
		asm_init_instruct(inst);
	(*inst)->opc = asm_opcode(splited_line, g_op_tab);
	j = 0;
	while (splited_line[j] != '\0'
	&& !ft_strchr("%:-0123456789", splited_line[j]))
		j++;
	if (splited_line[j] != '\0')
	{
		if (asm_which_param(splited_line + j) != -1)
			asm_check_inst(data, inst, splited_line + j, i);
		else
			asm_handle_error(data, i[0], j,
				"Syntax error, parameter wanted");
	}
}

void	asm_parse_comment(int *i)
{
	i[4] = TRUE;
	i[2] = TRUE;
}

void	asm_check_inst(t_data *data, t_inst **inst, char *splited_line, int *i)
{
	if (*inst == NULL)
		asm_handle_error(data, i[0], i[1], "Opcode missing");
	if ((*inst)->nbparams == g_op_tab[(*inst)->opc].param_number)
		asm_handle_error(data, i[0], i[1],
			"Too much parameters in this instruction");
	asm_parse_params(data, inst, splited_line, i);
}

/*
**	j[0] : line number
**	j[1] : column of token
**	j[2] : token recognized bool
**	j[3] : index of split_line
**	j[4] : active comment bool
**	j[5] : type of parameter
**	j[6] : index 2 in splited_line
*/

void	asm_parse(t_data *data, char **sline, int nu, char *line)
{
	t_inst		*inst;
	int			j[7];

	j[3] = 0;
	j[4] = FALSE;
	inst = NULL;
	j[0] = nu;
	while (sline[j[3]] != NULL)
	{
		j[2] = FALSE;
		j[1] = asm_err_col(line, sline[j[3]]);
		if (j[4] == FALSE && asm_is_label(sline[j[3]]) != -1)
			asm_parse_label(data, &inst, sline[j[3]], j);
		else if (j[4] == FALSE && (asm_opcode(sline[j[3]], g_op_tab) != -1))
			asm_parse_opcode(data, &inst, sline[j[3]], j);
		else if (j[4] == FALSE && asm_which_param(sline[j[3]]) != -1)
			asm_check_inst(data, &inst, sline[j[3]], j);
		else if (j[4] == 1 || sline[j[3]][0] == '#' || sline[j[3]][0] == ';')
			asm_parse_comment(j);
		else if (j[2] == FALSE)
			asm_handle_error(data, nu, j[1], "Token not recognized");
		j[3]++;
	}
	if (inst != NULL)
		asm_add_inst(data, &(data->inst), inst, g_op_tab);
}
