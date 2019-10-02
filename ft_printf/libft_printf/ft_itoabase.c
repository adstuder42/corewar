/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 04:33:17 by schabbi           #+#    #+#             */
/*   Updated: 2019/08/13 00:31:58 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static char	in_to_base(uintmax_t nbr)
{
	char *base;

	base = "0123456789ABCDEF";
	return (base[nbr]);
}

static char	*sign_ret(uintmax_t nbr, char *ret)
{
	if (nbr == 0)
		ret[0] = '0';
	return (ret);
}

char		*ft_itoabase(uintmax_t nbr, int base)
{
	uintmax_t	lg_nbr;
	char		*ret;
	int			len;
	uintmax_t	tmp;

	lg_nbr = nbr;
	len = 1;
	tmp = lg_nbr;
	while (lg_nbr /= (uintmax_t)base)
		len++;
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len] = 0;
	while (tmp)
	{
		ret[--len] = in_to_base(tmp % base);
		tmp /= base;
	}
	return (sign_ret(nbr, ret));
}
