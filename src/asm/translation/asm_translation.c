/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:52 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 02:40:26 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_prog_translate(t_data *data, t_inst *insts, unsigned char *corfile,
			t_op *op_tab)
{
	int				i;
	t_inst			*first;
	static void		(*f[17])(t_data *, t_inst *, unsigned char *, t_op *) = {
		asm_live, asm_ld, asm_st, asm_add, asm_sub, asm_and, asm_or, asm_xor,
		asm_zjmp, asm_ldi, asm_sti, asm_fork, asm_lld, asm_lldi, asm_lfork,
		asm_aff, asm_null};

	first = insts;
	i = 1;
	while (insts != NULL)
	{
		if (i == 1)
			data->start_prog = data->nb_bytes;
		f[insts->opc](data, insts, corfile, op_tab);
		insts = insts->next;
		i++;
	}
	insts = first;
}

void	asm_wtranslation(t_data *data, t_op *optab)
{
	unsigned char	corfile[MAX_COR_SIZE];
	t_inst			*insts;
	int				prog_size;

	ft_bzero(corfile, MAX_COR_SIZE);
	data->buflen = 0;
	asm_check_labels(data);
	asm_header_translate(data, corfile);
	insts = data->inst;
	asm_prog_translate(data, insts, corfile, optab);
	if (data->buflen > 0)
	{
		asm_openwr(data);
		write(data->fd, corfile, data->buflen);
		ft_bzero(corfile, MAX_COR_SIZE);
		data->buflen = 0;
	}
	asm_label_call(data);
	free_label_calls(data->label_call);
	prog_size = data->nb_bytes - data->start_prog;
	asm_cor_uileeks(data, prog_size, data->size_place);
	(void)optab;
}
