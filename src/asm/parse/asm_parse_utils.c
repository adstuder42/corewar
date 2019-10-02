/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:50:42 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 19:21:46 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_stuck_opcode(t_data *data, t_inst **inst, char *sline,
			int *i)
{
	int		len;

	len = 0;
	while (sline[len] != '\0'
	&& ft_strchr(LABEL_CHARS, sline[len]))
		len++;
	if (!((*inst)->label[0] = ft_strndup(sline, len)))
		asm_memerr(data);
	len++;
	if (asm_opcode(sline + len, g_op_tab) != -1)
		asm_parse_opcode(data, inst, sline + len, i);
	else if (sline[len] == COMMENT_CHAR || sline[len] == ';')
		asm_parse_comment(i);
	else
		asm_handle_error(data, i[0], len, "Syntax error, opcode wanted");
}

void	asm_comment_afterhead(t_data *data, char *line, int *i)
{
	i[0] = ++i[1];
	while (line[i[1]] != '\0' && ft_strchr(" \t", line[i[1]]))
		i[1]++;
	if (line[i[1]] != '\0' && line[i[1]] != '#' && line[i[1]] != ';')
		asm_handle_error(data, i[3], i[0],
			"Only comment token (not comment program) are authorized on the "
			"same line of name or comment program");
}

void	asm_stuck_reg(t_data *data, char *sline, int len, int *i)
{
	if (sline[len + 1] != '\0')
	{
		if (sline[len + 1] == '#' || sline[len + 1] == ';')
			asm_parse_comment(i);
		else
			asm_handle_error(data, i[0], len, "Syntax Xerror: only "
				"'#' or ';' are permitted just after (without space) "
				"parameter");
	}
}

void	asm_parse_reg(t_data *data, t_inst **ins, char *sline, int *i)
{
	long long int	number;
	int				len;
	int				j;

	number = ft_atolli(sline + 1);
	len = ft_intlen(number);
	j = 0;
	while (sline[j + 1] == '0')
		j++;
	if (number == 0)
		j--;
	if (number >= 0 && number <= 99)
	{
		(*ins)->params[(*ins)->nbparams].type = reg_exp;
		if (!((*ins)->params[(*ins)->nbparams].val.reg.reg_exp = ft_strdup(
				sline)))
			asm_memerr(data);
		(*ins)->params[(*ins)->nbparams].val.reg.value = (int)number;
		(*ins)->nbparams++;
		len = len + j;
		asm_stuck_reg(data, sline, len, i);
	}
	else
		asm_handle_error(data, i[0], i[1], "Syntax error for register");
}

void	asm_catch_val_indlab(t_data *data, t_inst **inst, char *sline, int j)
{
	(*inst)->params[(*inst)->nbparams].type = ind_lab_exp;
	if (!((*inst)->params[(*inst)->nbparams].val.ind_lab = ft_strndup(
			sline + 1, j - 1)))
		asm_memerr(data);
}
