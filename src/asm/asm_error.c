/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:30:17 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 20:29:52 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_err_col(char *line, char *split_line)
{
	int		col;
	char	*ptr;

	col = 0;
	if (!(ptr = ft_strstr(line, split_line)))
		return (col);
	while (line != ptr)
	{
		if (*line == '\t')
			col += 4;
		else
			col++;
		line++;
	}
	return (col);
}

void	asm_handle_error(t_data *data, int line, int col, char *msg)
{
	t_asm_err	asm_errno;

	asm_errno.line = line;
	asm_errno.col = col + 1;
	if (!(asm_errno.msg = ft_strdup(msg)))
		asm_memerr(data);
	asm_free_header(data->raw_header);
	asm_free_insts(data->inst);
	asm_print_exit(asm_errno);
}

void	asm_print_exit(t_asm_err asm_errno)
{
	ft_printf("Error [%d,%d] : %s\n",
		asm_errno.line, asm_errno.col, asm_errno.msg);
	free(asm_errno.msg);
	exit(EXIT_FAILURE);
}

void	asm_handle_error2(t_data *data, t_asm_err asm_errno, int opcode,
			t_op *optab)
{
	asm_free_header(data->raw_header);
	asm_free_insts(data->inst);
	if (!(asm_errno.msg2 = ft_strdup(optab[opcode].opcode)))
		asm_memerr3();
	if (asm_errno.paramnb == -1)
	{
		if (!(asm_errno.typemsg = ft_strdup("count")))
		{
			free(asm_errno.msg2);
			asm_memerr3();
		}
	}
	else
	{
		asm_errno.typemsg = NULL;
		if (!(asm_errno.typemsg = ft_strdup("type")))
		{
			free(asm_errno.msg2);
			asm_memerr3();
		}
		asm_handle_error21(&asm_errno);
	}
	asm_print_exit2(asm_errno);
}

void	asm_print_exit2(t_asm_err asm_errno)
{
	if (asm_errno.paramnb == -1)
		ft_printf("%s %s %s %s\n", asm_errno.msg, asm_errno.typemsg,
			asm_errno.endmsg, asm_errno.msg2);
	else
	{
		ft_printf("%s %d %s %s %s %s\n", asm_errno.msg, asm_errno.paramnb,
			asm_errno.typemsg, asm_errno.typemsg2, asm_errno.endmsg,
			asm_errno.msg2);
		free(asm_errno.typemsg2);
	}
	free(asm_errno.msg);
	free(asm_errno.typemsg);
	free(asm_errno.endmsg);
	free(asm_errno.msg2);
	exit(EXIT_FAILURE);
}
