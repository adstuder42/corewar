/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate_header.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:18 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 03:56:26 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_init_header(t_data *data, t_header *header)
{
	t_head		*first;

	if (data->nb_name_prog != 1 || data->nb_comment_prog != 1)
		asm_handle_error(data, 1, 0, "No name or comment for program !");
	header->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	ft_bzero(header->comment, COMMENT_LENGTH);
	first = data->raw_header;
	while (data->raw_header != NULL)
	{
		if (data->raw_header->type == prog_name_exp)
			ft_strcat(header->prog_name, data->raw_header->val);
		else if (data->raw_header->type == prog_comment_exp)
			ft_strcat(header->comment, data->raw_header->val);
		data->raw_header = data->raw_header->next;
	}
	data->raw_header = first;
}

void	asm_header_translate(t_data *data, unsigned char *corfile)
{
	t_header	head;

	asm_init_header(data, &head);
	asm_cor_uintcpy(data, corfile, head.magic, 4);
	asm_cor_memcpy(data, corfile, PROG_NAME_LENGTH, head.prog_name);
	asm_cor_uintcpy(data, corfile, 0, 4);
	data->size_place = data->nb_bytes;
	head.prog_size = 0;
	asm_cor_uintcpy(data, corfile, head.prog_size, 4);
	asm_cor_memcpy(data, corfile, COMMENT_LENGTH, head.comment);
	asm_cor_uintcpy(data, corfile, 0, 4);
}
