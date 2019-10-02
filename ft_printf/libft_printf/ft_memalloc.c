/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:34:12 by schabbi           #+#    #+#             */
/*   Updated: 2018/04/13 19:29:18 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*nzm;
	size_t	i;

	i = 0;
	if (!(nzm = malloc(size)))
		return (0);
	while (i < size)
	{
		nzm[i] = 0;
		i++;
	}
	return ((void*)(nzm));
}
