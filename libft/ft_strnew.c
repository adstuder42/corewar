/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 15:52:58 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/09 16:10:31 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(size + 1)))
		return (NULL);
	ft_memset(tmp, '\0', size + 1);
	return (tmp);
}
