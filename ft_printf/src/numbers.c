/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 08:54:14 by schabbi           #+#    #+#             */
/*   Updated: 2019/03/11 15:38:21 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include <limits.h>
#include <stdint.h>
#include "../ft_printf.h"

void	ft_cast(int *fl, long long *n_, va_list ls)
{
	if ((fl[12] || fl[10] || fl[11] || fl[8] || fl[9]) && (fl[23] || fl[21]))
	{
		*n_ = (fl[23]) ? (long long int)va_arg(ls, size_t) : *n_;
		*n_ = (fl[21]) ? va_arg(ls, int) : *n_;
		return ;
	}
	if ((fl[8] || fl[9] || fl[12]) && !fl[20] && !fl[22])
		*n_ = va_arg(ls, unsigned int);
	else
	{
		if ((fl[5] || fl[14]) && !fl[20] && !fl[22] && !fl[23])
			*n_ = va_arg(ls, int);
		else
			*n_ = va_arg(ls, intmax_t);
	}
	if (fl[21] && !fl[13])
	{
		*n_ = (*n_ > SHRT_MAX) ? *n_ * -1 : *n_;
		if (fl[24])
		{
			*n_ = (*n_ > CHAR_MAX) ? CHAR_MIN - (CHAR_MIN + *n_) : *n_;
			*n_ = (*n_ < CHAR_MIN) ? -CHAR_MIN + (-CHAR_MIN + *n_) : *n_;
		}
	}
}

char	*prepare_num(long long *d_, int *fl, va_list ls, char *sign)
{
	char	*out_put;
	int		base;

	base = (10 + (6 * (fl[8] + fl[9] + fl[18]))) + (-2 * (fl[10] + fl[11]));
	ft_cast(fl, d_, ls);
	*sign = ((*d_ < 0) && !(fl[8] || fl[9] || fl[12] || fl[13] || fl[10]
				|| fl[11])) ? '-' : '+';
	if ((*d_ < 0) && (fl[5] || fl[14]))
		out_put = ft_itoabase(-*d_, base);
	else
		out_put = ft_itoabase(*d_, base);
	if ((*d_ > UINT_MAX) && (fl[8] || fl[9]) && !fl[20] && !fl[22] && !fl[23])
	{
		ft_bzero(out_put, ft_strlen(out_put));
		out_put[0] = '0';
	}
	if (fl[8] || fl[18])
		ft_tolowercase(out_put);
	if ((*d_ == 0) && fl[18])
		out_put = "0x0";
	return (out_put);
}

void	output_the_num(t_buffer *buf, char *num, int *fl, char sign)
{
	int		i;
	char	*h_tag;

	i = 0;
	if ((!fl[3]) || fl[1] || ((fl[10] || fl[11]) && !fl[3]))
	{
		h_tag = (fl[8] || fl[9] || fl[18]) ? ft_strdup("0X") : ft_strdup("0");
		if (fl[8] || fl[18])
			ft_tolowercase(h_tag);
		if ((fl[0] || fl[18]) && num[0] != '0')
			ft_putstr_onbuf(buf, h_tag, 1 - (fl[10] + fl[11]));
		free(h_tag);
	}
	if (((fl[2]) || (sign == '-')) && !fl[12] && !fl[3])
		ft_putchar_onbuf(buf, sign);
	if (fl[25] > 0)
		while (i < fl[25])
		{
			ft_putchar_onbuf(buf, '0');
			i++;
		}
	ft_putstr_onbuf(buf, num, (long long int)ft_strlen(num) - 1);
}

void	ft_precision(int *fl, char *num, int *width)
{
	int	tmp_w;

	if ((fl[26] == 0) && fl[18] && !fl[1])
		*width += 2;
	(fl[30]) ? fl[3] = 0 : 0;
	if (fl[25] && fl[26] && fl[0] && (fl[10] || fl[11]))
		fl[25]--;
	tmp_w = *width;
	fl[25]++;
	if ((int)ft_strlen(num) >= fl[25])
		fl[25] = 0;
	if (fl[25])
	{
		if ((*width) > fl[25])
		{
			*width -= fl[25];
			*width += (int)ft_strlen(num);
		}
		if (tmp_w <= fl[25])
			*width = (int)ft_strlen(num);
	}
	if ((int)ft_strlen(num) < fl[25])
		fl[25] -= (int)ft_strlen(num);
}

int		d(t_buffer *buf, int width, int *fl, va_list ls)
{
	char			*num;
	char			sign;
	long	long	d_;

	d_ = 0;
	num = prepare_num(&d_, fl, ls, &sign);
	fl[27] = (!d_ && fl[25] == -1) ? 1 : fl[27];
	fl[27] = (fl[0] && ((fl[10] || fl[11]))) ? 0 : fl[27];
	fl[26] = d_;
	ft_precision(fl, num, &width);
	if ((fl[2]) || d_ < 0)
	{
		width--;
		if ((fl[3]) || ((fl[30] < 0) && fl[27]))
			ft_putchar_onbuf(buf, sign);
	}
	if (fl[4] && sign == '+' && !fl[2] && fl[25] <= 0 && !fl[12])
		ft_putchar_onbuf(buf, ' ');
	((fl[25]) && fl[4]) ? fl[4]-- : 0;
	(!fl[1]) ? rv_width(buf, width - ft_strlen(num) + fl[27] - fl[4], fl) : 0;
	(!fl[27]) ? output_the_num(buf, num, fl, sign) : 0;
	(fl[1]) ? rv_width(buf, width - ft_strlen(num) + fl[27] - fl[4], fl) : 0;
	if (!(fl[18] && fl[26] == 0))
		free(num);
	return (1);
}
