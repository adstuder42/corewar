/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 11:27:29 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/06 11:35:26 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = (char *)s1;
	tmp2 = (char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (n != 0)
	{
		if (tmp1[i] != tmp2[i])
			return ((unsigned char)tmp1[i] - (unsigned char)tmp2[i]);
		i++;
		n--;
	}
	return (0);
}
