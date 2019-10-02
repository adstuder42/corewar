/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:30:29 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/12 11:29:24 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;
	int				i;

	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned char *)src;
	i = 0;
	while (n != 0)
	{
		tmpdst[i] = tmpsrc[i];
		if (tmpsrc[i] == (unsigned char)c)
			return (tmpdst + i + 1);
		i++;
		n--;
	}
	return (NULL);
}
