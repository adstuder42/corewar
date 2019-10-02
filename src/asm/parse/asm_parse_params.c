/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:01 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/21 12:16:07 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_catch_val_dirlab(t_data *data, t_inst **inst, char *sline, int j)
{
	(*inst)->params[(*inst)->nbparams].type = dir_lab_exp;
	if (!((*inst)->params[(*inst)->nbparams].val.dir_lab = ft_strndup(
			sline + 2, j - 2)))
		asm_memerr(data);
}

void	asm_catch_val_nb(t_inst **ins, long long int nb, int type)
{
	int				dir_types[16];

	asm_init_dir_types(dir_types);
	if (type == dir_int_exp)
	{
		(*ins)->params[(*ins)->nbparams].type = dir_int_exp;
		if (dir_types[(*ins)->opc] == T_SHORT)
			(*ins)->params[(*ins)->nbparams].val.dir_int = (unsigned short int)
				nb;
		else
			(*ins)->params[(*ins)->nbparams].val.dir_int = (unsigned int)nb;
	}
	else if (ind_int_exp)
	{
		(*ins)->params[(*ins)->nbparams].type = ind_int_exp;
		(*ins)->params[(*ins)->nbparams].val.ind_int = (unsigned short int)nb;
	}
}

void	asm_parse_is_digit(t_data *data, t_inst **inst, char *sline,
			int *i)
{
	long long int	number;
	int				j;
	int				len;

	number = ft_atolli(sline + i[6]);
	len = ft_intlen(number);
	j = 0;
	while (sline[i[6] + j] == '0')
		j++;
	if (number == 0)
		j--;
	if (i[5] == T_DIR)
		asm_catch_val_nb(inst, number, dir_int_exp);
	else
		asm_catch_val_nb(inst, number, ind_int_exp);
	(*inst)->nbparams++;
	if (sline[len + i[6] + j] != '\0')
	{
		if (sline[len + i[6] + j] == '#' || sline[len + i[6] + j] == ';')
			asm_parse_comment(i);
		else
			asm_handle_error(data, i[0], len + i[6] + j, "Syntax error: only "
			"#' or ';' are permitted just after (without space) parameter");
		(void)data;
	}
}

void	asm_parse_un_dir(t_data *data, t_inst **inst, char *sline,
			int *i)
{
	if (sline[i[6]] == LABEL_CHAR)
	{
		i[6]++;
		while (sline[i[6]] != '\0'
		&& ft_strchr(LABEL_CHARS, sline[i[6]]))
			i[6]++;
		if (i[5] == T_DIR)
			asm_catch_val_dirlab(data, inst, sline, i[6]);
		else
			asm_catch_val_indlab(data, inst, sline, i[6]);
		(*inst)->nbparams++;
		if (sline[i[6]] != '\0')
		{
			if (ft_strchr("#;", sline[i[6]]))
				asm_parse_comment(i);
			else
				asm_handle_error(data, i[0], i[6],
					"Syntax error: only '#' or ';' are permitted just after "
					"(without space) parameter");
		}
	}
	else if (sline[i[6]] == '-' || ft_isdigit(sline[i[6]]))
		asm_parse_is_digit(data, inst, sline, i);
	else
		asm_handle_error(data, i[0], i[1], "Must be a :label or a number");
}

void	asm_parse_params(t_data *data, t_inst **inst, char *splited_line,
			int *i)
{
	i[2] = TRUE;
	i[5] = asm_which_param(splited_line);
	if (i[5] == T_REG)
		asm_parse_reg(data, inst, splited_line, i);
	else if (i[5] == T_IND)
	{
		i[6] = 0;
		asm_parse_un_dir(data, inst, splited_line, i);
	}
	else if (i[5] == T_DIR)
	{
		i[6] = 1;
		asm_parse_un_dir(data, inst, splited_line, i);
	}
	else
		asm_handle_error(data, i[0], i[1], "Wrong param for this instruction");
}
