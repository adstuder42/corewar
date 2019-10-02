/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:05:49 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/16 14:13:22 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	unsigned int	j;
	unsigned int	k;
	size_t			src_len;

	if (size == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	while (dst[j] && j < size)
		j++;
	k = 0;
	while (src[k] != '\0' && j < size - 1)
	{
		dst[j] = src[k];
		j++;
		k++;
	}
	if (size && size >= i)
		dst[j] = '\0';
	src_len = ft_strlen(src);
	if (size < i)
		return (src_len + size);
	else
		return (src_len + i);
}
