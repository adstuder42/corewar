/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate_buf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:38:14 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 01:11:52 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_cor_uintcpy(t_data *data, unsigned char *corfile, unsigned int nb,
			size_t byt)
{
	unsigned char	*to_cpy;

	to_cpy = asm_uint_to_char(data, nb, byt);
	if (data->buflen + byt < MAX_COR_SIZE)
	{
		ft_memcpy(corfile + data->buflen, to_cpy, sizeof(unsigned char) * byt);
		data->buflen += byt;
	}
	else if (byt > MAX_COR_SIZE)
	{
		asm_openwr(data);
		asm_write(data, corfile);
		write(data->fd, to_cpy, byt);
	}
	else
	{
		asm_openwr(data);
		asm_write(data, corfile);
		ft_memcpy(corfile + data->buflen, to_cpy, sizeof(unsigned char) * byt);
		data->buflen += byt;
	}
	data->nb_bytes += byt;
	free(to_cpy);
}

void	asm_cor_usileeks(t_data *data, unsigned short int nb, int addr)
{
	unsigned char	*to_cpy;

	to_cpy = asm_uint_to_char(data, nb, 2);
	lseek(data->fd, addr, SEEK_SET);
	write(data->fd, to_cpy, 2);
	free(to_cpy);
}

void	asm_cor_uileeks(t_data *data, unsigned int nb, int addr)
{
	unsigned char	*to_cpy;

	to_cpy = asm_uint_to_char(data, nb, 4);
	lseek(data->fd, addr, SEEK_SET);
	write(data->fd, to_cpy, 4);
	free(to_cpy);
}

void	asm_cor_memcpy(t_data *data, unsigned char *corfile, int size,
			char *to_cpy)
{
	if (data->buflen + size < MAX_COR_SIZE)
	{
		ft_memcpy(corfile + data->buflen, to_cpy,
			sizeof(unsigned char) * size);
		data->buflen += size;
	}
	else if (size > MAX_COR_SIZE)
	{
		asm_openwr(data);
		asm_write(data, corfile);
		write(data->fd, to_cpy, size);
	}
	else
	{
		asm_openwr(data);
		asm_write(data, corfile);
		ft_memcpy(corfile + data->buflen, to_cpy,
			sizeof(unsigned char) * size);
		data->buflen += size;
	}
	data->nb_bytes += size;
}

void	asm_cor_memcpy1(t_data *data, unsigned char *corfile, int size,
			unsigned char to_cpy)
{
	if (data->buflen + size < MAX_COR_SIZE)
		ft_memcpy(corfile + data->buflen, &to_cpy,
			sizeof(unsigned char) * size);
	else
	{
		asm_openwr(data);
		asm_write(data, corfile);
		ft_memcpy(corfile + data->buflen, &to_cpy,
			sizeof(unsigned char) * size);
	}
	data->buflen += size;
	data->nb_bytes += size;
}
