/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:21:47 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/16 14:11:56 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*tmp;

	tmp = (char *)b;
	i = 0;
	while (len != 0)
	{
		tmp[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
