/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 11:08:20 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/16 14:10:33 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	int				i;

	tmp = (unsigned char *)s;
	i = 0;
	while (n != 0)
	{
		if (tmp[i] == (unsigned char)c)
			return (tmp + i);
		i++;
		n--;
	}
	return (NULL);
}
