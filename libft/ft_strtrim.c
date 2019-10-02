/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:43:10 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/16 14:02:59 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned int		nb_startingspaces(char const *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}

char					*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*res;

	if (s == NULL)
		return (NULL);
	k = nb_startingspaces(s);
	if (s[k] == '\0')
		return (ft_strnew(0));
	i = ft_strlen(s) - 1;
	j = i - k + 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i--;
		j--;
	}
	if (!(res = (char *)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	k = 0;
	i = i - j + 1;
	while (k < j)
		res[k++] = s[i++];
	res[k] = '\0';
	return (res);
}
