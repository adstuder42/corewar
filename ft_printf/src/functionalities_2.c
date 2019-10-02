/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionalities_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:52:27 by schabbi           #+#    #+#             */
/*   Updated: 2019/03/11 15:39:43 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_first_byte(int *mask, char *tab, int *c_size, int *fl)
{
	tab[0] = fl[28] >> ((*c_size / 6) * 6);
	if ((8 - ((*c_size / 6) + 1)) <= count_bits(tab[0], 2))
		tab[0] = tab[0] >> 1;
	*mask = (0xF0 >> (7 - (*c_size / 6))) << (7 - (*c_size / 6));
	tab[0] = (tab[0] | *mask);
	fl[28] = fl[28] - ((fl[28] >> ((*c_size / 6) * 6)) << ((*c_size / 6) * 6));
}

void	flagtheflags_3(int *fl, int *conv)
{
	if (fl[20] && fl[6])
	{
		fl[6] = 0;
		fl[17] = 1;
		*conv = 12;
	}
	if (fl[20] && fl[16])
	{
		fl[16] = 0;
		fl[19] = 1;
		*conv = 14;
	}
}

int		is_sub_arr(uintmax_t big_nbr, uintmax_t div, int *fl, double nbr)
{
	uintmax_t	first_num;

	if ((fl[0] + 1) != (count_bits((int)nbr, 10) + fl[25]))
		return (0);
	div /= 10;
	first_num = (big_nbr != 0) ? big_nbr / div : 0;
	if (first_num > 5)
		return (1);
	return (0);
}

int		ft_putwstr_onbuf(t_buffer *buf, int *fl, int str_len, wchar_t *str)
{
	long	i;
	int		size;
	int		tmp_fl30;

	tmp_fl30 = fl[30] + 1;
	(void)str_len;
	i = 0;
	while (str[i])
	{
		size = (count_bits(str[i], 2) == 17) ? 4
			: (count_bits(str[i], 2) / 6) + 1;
		size = (str[i] >= 254) ? size : 1;
		tmp_fl30 -= size;
		if (size > 1 || fl[30] == -1 || i)
			if (fl[30])
				if (tmp_fl30 < 0)
					break ;
		fl[19] = str[i];
		fl[17] = 1;
		if (!big_c(buf, 0, fl, 0))
			return (0);
		i++;
	}
	return (1);
}

int		count_bits(uintmax_t nbr, int base)
{
	int	ret;

	ret = 0;
	while (nbr)
	{
		nbr /= base;
		ret++;
	}
	return (ret);
}
