/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:32:19 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:32:20 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_is_prog_head(t_data *data, char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != '\0' && ft_strchr(" \t", buffer[i]))
		i++;
	if (!ft_strncmp(".name", buffer + i, 5))
		return (1);
	else if (!ft_strncmp(".comment", buffer + i, 8))
		return (2);
	else if (data->head_type == 1)
		return (1);
	else if (data->head_type == 2)
		return (2);
	return (-1);
}

int		asm_is_label(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != '\0' && ft_strchr(LABEL_CHARS, buffer[i]))
		i++;
	if (buffer[i] == LABEL_CHAR)
	{
		if (buffer[++i] == '\0')
			return (1);
		else if (i != 1)
			return (2);
	}
	return (-1);
}

int		asm_opcode(char *buffer, t_op *op_tab)
{
	int		i;
	int		j;

	j = 0;
	while (buffer[j] != '\0' && !ft_strchr("%:-0123456789", buffer[j]))
		j++;
	i = 0;
	while (i < 16)
	{
		if (j != 0 && !ft_strncmp(op_tab[i].opcode, buffer, j))
			return (i);
		i++;
	}
	return (-1);
}

int		asm_which_param(char *buffer)
{
	if (buffer[0] == 'r')
		return (T_REG);
	else if (buffer[0] == '%')
		return (T_DIR);
	else if (buffer[0] == ':')
		return (T_IND);
	else if (ft_isdigit(buffer[0]) || buffer[0] == '-')
		return (T_IND);
	else
		return (-1);
}
