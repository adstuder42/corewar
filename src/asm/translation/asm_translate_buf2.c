/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate_buf2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 01:11:14 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 01:14:09 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			asm_openwr(t_data *data)
{
	if (data->write == 0)
	{
		if ((data->fd = open(data->fnameout, O_CREAT | O_WRONLY | O_TRUNC,
			0644)) == -1)
		{
			perror("Error for writing file");
			asm_free_header(data->raw_header);
			asm_free_insts(data->inst);
			free(data->fnameout);
			close(data->fdin);
			exit(EXIT_FAILURE);
		}
		ft_printf("Writing output program to %s\n", data->fnameout);
		data->write = 1;
	}
}

unsigned char	*asm_uint_to_char(t_data *data, unsigned int nb, size_t byt)
{
	int				i;
	int				j;
	unsigned char	*res;

	if (!(res = (unsigned char *)malloc(sizeof(unsigned char) * byt)))
		asm_memerr(data);
	i = byt - 1;
	j = 0;
	while (i >= 0)
		res[j++] = (unsigned char)((unsigned char *)&nb)[i--];
	return (res);
}

void			asm_write(t_data *data, unsigned char *corfile)
{
	write(data->fd, corfile, data->buflen);
	ft_bzero(corfile, MAX_COR_SIZE);
	data->buflen = 0;
}
