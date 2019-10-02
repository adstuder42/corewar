/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:33:23 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 02:47:44 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*result;
	int		i;

	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && len != 0)
	{
		result[i] = s1[i];
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}
