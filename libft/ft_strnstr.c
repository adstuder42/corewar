/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:34:08 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/13 15:31:28 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	int		k;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && len != 0)
	{
		j = 0;
		k = len;
		while ((haystack[i + j] == needle[j]) || (needle[j] == '\0'))
		{
			if (k == 0 && needle[j] != '\0')
				return (NULL);
			else if (needle[j] == '\0')
				return ((char *)haystack + i);
			k--;
			j++;
		}
		len--;
		i++;
	}
	return (NULL);
}
