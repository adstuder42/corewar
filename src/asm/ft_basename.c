/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:33:01 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 02:30:08 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_basename(char *s)
{
	char	*ptr;
	int		len;
	char	*res;

	if ((ptr = ft_strrchr(s, '.')) == NULL)
		return (NULL);
	len = 0;
	while (s + len != ptr)
		len++;
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	while (s + len != ptr)
	{
		res[len] = s[len];
		len++;
	}
	res[len] = '\0';
	return (res);
}
