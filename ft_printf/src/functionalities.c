/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionalitys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 09:17:12 by schabbi           #+#    #+#             */
/*   Updated: 2018/11/08 22:32:34 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <stdint.h>

int		check_valid_flag(char c)
{
	char	*fl;
	int		i;

	i = 0;
	fl = "hljz #0+-.";
	if (c > '0' && c <= '9')
		return (1);
	while (fl[i])
	{
		if (fl[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		print_part(const char *restrict format,
		int *i, t_buffer *buf, va_list ls)
{
	int	format_length;

	if (format[*i] == '%')
	{
		if (!(format_length = solve_format(format + *i + 1, ls, buf)))
			return (-1);
		*i += format_length;
	}
	else
		ft_putchar_onbuf(buf, format[*i]);
	return (0);
}

int		ft_putchar_onbuf(t_buffer *buf, char c)
{
	if ((buf->buf_len) == BUF_SIZE)
	{
		write(1, buf->str, buf->buf_len);
		ft_bzero(buf->str, BUF_SIZE);
		buf->str_len += buf->buf_len;
		buf->buf_len = 0;
	}
	buf->str[buf->buf_len] = c;
	buf->buf_len++;
	return (0);
}

void	flagtheflags_2(int *flags, char *tmp, int converter)
{
	int		i;
	int		j;
	char	*flag_2;

	flag_2 = "lhjz";
	j = 0;
	i = 0;
	flags[converter + 5] = 1;
	while (tmp[i])
		i++;
	if (i > 0)
		i--;
	while (flag_2[j])
	{
		if (flag_2[j] == tmp[i])
			flags[20 + j] = 1;
		j++;
	}
	if (flags[20] || flags[21])
		if (i > 0)
			if (tmp[i] == tmp[i - 1])
				flags[24] = 1;
}

int		ft_putstr_onbuf(t_buffer *buf, char *str, long long int buf_len)
{
	long	long	int	i;

	i = 0;
	while (i <= buf_len)
	{
		ft_putchar_onbuf(buf, str[i]);
		i++;
	}
	return (0);
}
