/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 09:27:40 by schabbi           #+#    #+#             */
/*   Updated: 2019/03/11 15:42:19 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include "../ft_printf.h"
#include <limits.h>

void	rv_width(t_buffer *buf, int width, int *fl)
{
	int		i;
	char	c;
	char	*h_tag;

	width = (fl[18]) ? width - 2 : width;
	i = -1;
	width += (fl[0] * (((fl[10] || fl[11]) && fl[26] <= 0)));
	if (fl[0] && (fl[8] || fl[9] || fl[18] || fl[10] || fl[11])
			&& (fl[10] || fl[11] || fl[26]))
		width -= 2 - (1 * (fl[10] + fl[11] + fl[18]));
	c = (fl[7] && fl[3]) ? '0' : ' ';
	if ((fl[3]) && !fl[1])
	{
		h_tag = ft_strdup("0X");
		if (fl[8])
			ft_tolowercase(h_tag);
		if (fl[0] && (fl[8] || fl[9] || fl[18]) && !fl[27] && fl[26])
			ft_putstr_onbuf(buf, h_tag, 1);
		if ((!fl[1]) && (!fl[30]))
			c = '0';
		free(h_tag);
	}
	while (++i < width)
		ft_putchar_onbuf(buf, c);
}

void	flagtheflags(int *fl, int *width, char *tmp)
{
	char	*flag;
	int		i[2];
	int		width_flag;

	width_flag = 0;
	i[0] = -1;
	flag = "#-+0 \0";
	while (tmp[++i[0]])
	{
		i[1] = -1;
		while (flag[++i[1]])
		{
			if (!width_flag)
				fl[i[1]] = (tmp[i[0]] == flag[i[1]]) ? 1 : fl[i[1]];
			if (tmp[i[0]] >= '1' && tmp[i[0]] <= '9')
				if ((!width_flag) && !fl[30])
				{
					width_flag = 1;
					*width = ft_atoi(tmp + i[0]);
				}
			fl[30] = fl[25];
			fl[25] = (tmp[i[0]] == '.') ? ft_atoi(tmp + i[0] + 1) - 1 : fl[25];
			fl[25] = ((tmp[i[0]] == '.') && !fl[25]) ? -2 : fl[25];
		}
	}
}

int		ft_dispatch(va_list ls, char *tmp, int converter, t_buffer *buf)
{
	int					flags[31];
	int					width;
	static	int			(*f[17])(t_buffer *, int, int *, va_list) = {d, ch,
		ch, d, d, d, d, d, d, d, d, ft_s,
		big_c, d, big_s, ft_bin, ft_flt};
	int					i;

	ft_bzero(flags, 31 * sizeof(int));
	width = 0;
	flagtheflags(flags, &width, tmp);
	flagtheflags_2(flags, tmp, converter);
	flagtheflags_3(flags, &converter);
	i = -1;
	free(tmp);
	if (flags[14])
	{
		flags[14] = 0;
		flags[5] = 1;
	}
	while (i++ < 16)
		if (converter == i)
			if (f[i](buf, width, flags, ls))
				return (1);
	return (0);
}

int		solve_format(const char *restrict format, va_list ls, t_buffer *buf)
{
	int		i;
	int		j;
	char	*conv;
	char	*tmp;

	conv = "dc%xXoOuUiDsCpSbf\0";
	i = -1;
	while (format[i++])
	{
		j = -1;
		while (conv[++j])
			if (conv[j] == format[i])
			{
				tmp = ft_strdup(format);
				tmp[i] = 0;
				if (!ft_dispatch(ls, tmp, j, buf))
					return (0);
				return (i + 1);
			}
		if (!check_valid_flag(format[i]))
			break ;
	}
	return (0);
}

int		ft_printf(const char *restrict format, ...)
{
	int			i;
	va_list		ls;
	t_buffer	buf;

	i = 0;
	ft_bzero(buf.str, BUF_SIZE);
	buf.str_len = 0;
	buf.buf_len = 0;
	va_start(ls, format);
	while (1)
	{
		if (!format[i])
		{
			i = 0;
			write(1, buf.str, buf.buf_len);
			buf.str_len += buf.buf_len;
			break ;
		}
		if (print_part(format, &i, &buf, ls) == -1)
			return (-1);
		i++;
	}
	return (buf.str_len);
}
