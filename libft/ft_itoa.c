/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:09:28 by xburelle          #+#    #+#             */
/*   Updated: 2019/03/19 15:43:59 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	intlen(long n)
{
	int		i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	long			nb;
	char			*res;
	unsigned int	i;
	int				len;

	nb = n;
	len = intlen(nb);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		res[0] = '0';
	i = len - 1;
	while (nb != 0)
	{
		res[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	res[len] = '\0';
	return (res);
}
