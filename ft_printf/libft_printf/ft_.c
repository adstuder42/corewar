/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:30:25 by schabbi           #+#    #+#             */
/*   Updated: 2018/04/21 12:07:44 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../ft_printf.h"

char			*ft_itoa(int n)
{
	char			*res;
	int				un;
	int				neg;
	int				len;

	len = 1;
	neg = (n < 0) ? -1 : 1;
	un = n;
	while (un /= 10)
		len++;
	len += (neg == -1) ? 1 : 0;
	if (!(res = (char *)ft_memalloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_memset((void*)res, '0', len);
	if (neg == -1)
		res[0] = '-';
	while (n)
	{
		res[--len] += (n % 10) * neg;
		n /= 10;
	}
	return (res);
}
