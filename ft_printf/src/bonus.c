/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 00:53:44 by schabbi           #+#    #+#             */
/*   Updated: 2018/10/27 01:51:46 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_bin(t_buffer *buf, int width, int *fl, va_list ls)
{
	uintmax_t	i;
	char		*out;

	(void)width;
	(void)fl;
	i = va_arg(ls, uintmax_t);
	out = ft_itoabase(i, 2);
	ft_putstr_onbuf(buf, out, ft_strlen(out));
	free(out);
	return (1);
}

int	ft_flt(t_buffer *buf, int width, int *fl, va_list ls)
{
	double		nbr;
	uintmax_t	first_num;
	uintmax_t	big_nbr;
	uintmax_t	div;

	nbr = va_arg(ls, double);
	if (!fl[25])
		fl[25] = 5 + (width * 0);
	else
		fl[25] = (fl[25] == -2) ? 0 : fl[25];
	fl[25]++;
	big_nbr = nbr * ft_power(10, fl[25] + 1);
	div = ft_power(10, count_bits(big_nbr, 10) - 1);
	while (fl[0] < (count_bits((int)nbr, 10) + fl[25]))
	{
		if (count_bits((int)nbr, 10) == fl[0])
			ft_putchar_onbuf(buf, '.');
		first_num = (big_nbr != 0) ? big_nbr / div : 0;
		big_nbr -= (first_num * div);
		ft_putchar_onbuf(buf, first_num + '0' + is_sub_arr(big_nbr
					, div, fl, nbr));
		div /= 10;
		fl[0]++;
	}
	return (1);
}
