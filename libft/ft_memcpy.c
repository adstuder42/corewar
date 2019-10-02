/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:24:57 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/05 16:36:32 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = (char *)dst;
	tmp2 = (char *)src;
	i = 0;
	while (n != 0)
	{
		tmp1[i] = tmp2[i];
		n--;
		i++;
	}
	return (dst);
}
