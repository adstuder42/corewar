/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:59:53 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 19:59:54 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int		ft_intbaselen(uintmax_t n, int base)
{
	int			i;
	long int	nb;

	i = 1;
	n = n / base;
	nb = n;
	while (nb > 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

int		ft_itoa_base2(uintmax_t n, char *buf)
{
	int		length;
	int		r;
	int		i;

	length = ft_intbaselen(n, 2);
	if (length == 7)
	{
		length++;
		buf[0] = '0';
	}
	i = length - 1;
	r = n % 2;
	buf[i--] = r + '0';
	while (n >= 2)
	{
		n /= 2;
		r = n % 2;
		buf[i--] = r + '0';
	}
	buf[length] = '\0';
	return (length);
}
