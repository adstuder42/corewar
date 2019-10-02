/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 06:47:59 by schabbi           #+#    #+#             */
/*   Updated: 2019/03/11 16:15:03 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	big_s(t_buffer *buf, int width, int *fl, va_list ls)
{
	wchar_t	*str;
	int		str_len;

	str = va_arg(ls, wchar_t *);
	str_len = (int)ft_wstrlen(str, fl[30]);
	width -= str_len;
	if (str)
		if (fl[25] && (str_len > fl[25]))
		{
			fl[25] = (fl[25] == -2) ? 0 : fl[25];
			str_len = fl[25] + 1;
		}
	if (!fl[1])
		rv_width(buf, width, fl);
	if (!str)
		ft_putstr_onbuf(buf, "(null)", 5);
	else if (!ft_putwstr_onbuf(buf, fl, str_len, str))
		return (0);
	if (fl[1])
		rv_width(buf, width, fl);
	return (1);
}

int	ft_putwchar_onbuf(t_buffer *buf, int width, int *fl, char *str)
{
	int	str_len;

	str_len = (int)ft_strlen(str);
	if (!fl[1])
		rv_width(buf, width - str_len, fl);
	if (!str)
		ft_putstr_onbuf(buf, "(null)", 5);
	else
		ft_putstr_onbuf(buf, str, str_len - 1);
	if (fl[1])
		rv_width(buf, width - str_len, fl);
	return (1);
}

int	big_c(t_buffer *buf, int width, int *fl, va_list ls)
{
	int		c_size;
	char	tab[5];
	int		mask;
	int		i;

	i = 1;
	fl[28] = fl[19] ? fl[19] : va_arg(ls, int);
	if ((fl[28] > 0x10ffff) || fl[28] < 0
			|| (fl[28] >= 0xD800 && fl[28] <= 0xDfff))
		return (0);
	c_size = (count_bits(fl[28], 2) == 17) ? 18 : count_bits(fl[28], 2);
	if (fl[28] <= 127)
		return (ch(buf, width, fl, ls));
	ft_first_byte(&mask, tab, &c_size, fl);
	while (i <= 3)
	{
		mask = 2 << ((c_size / 6) * 6);
		tab[i] = (mask | fl[28]) >> (count_bits(mask, 2) - 8);
		c_size -= 6;
		fl[28] -= ((fl[28] >> ((c_size / 6) * 6)) << ((c_size / 6) * 6));
		tab[++i] = 0;
	}
	return (ft_putwchar_onbuf(buf, width, fl, tab));
}

int	ft_s(t_buffer *buf, int width, int *fl, va_list ls)
{
	char	*str;
	int		str_len;

	str = va_arg(ls, char *);
	str_len = (int)ft_strlen(str);
	fl[30] = (!str && fl[30] > 6) ? 6 : fl[30];
	fl[30] = (!fl[30] && !str) ? 5 : fl[30];
	width = (!str) ? width - fl[30] - 1 : width;
	if (str)
		if (fl[25] && (str_len > fl[25]))
		{
			fl[25] = (fl[25] == -2) ? 0 : fl[25];
			str_len = fl[25] + 1;
		}
	if (!fl[1])
		rv_width(buf, width - (str_len), fl);
	if (!str)
		ft_putstr_onbuf(buf, "(null)", fl[30]);
	else
		ft_putstr_onbuf(buf, str, str_len - 1);
	if (fl[1])
		rv_width(buf, width - (str_len), fl);
	return (1);
}

int	ch(t_buffer *buf, int width, int *flags, va_list ls)
{
	char	c;

	if (!flags[17])
		c = (flags[7]) ? '%' : va_arg(ls, int);
	else
		c = flags[28];
	if (!flags[1])
		rv_width(buf, width - 1, flags);
	ft_putchar_onbuf(buf, c);
	if (flags[1])
		rv_width(buf, width - 1, flags);
	return (1);
}
