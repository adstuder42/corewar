/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:52:40 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/16 11:52:37 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = (char *)dst;
	tmp2 = (char *)src;
	if (src < dst)
	{
		while (len != 0)
		{
			tmp1[len - 1] = tmp2[len - 1];
			len--;
		}
	}
	else
	{
		i = 0;
		while (len != 0)
		{
			tmp1[i] = tmp2[i];
			len--;
			i++;
		}
	}
	return (tmp1);
}
