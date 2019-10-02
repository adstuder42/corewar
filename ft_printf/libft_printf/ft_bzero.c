/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 06:49:53 by schabbi           #+#    #+#             */
/*   Updated: 2018/05/17 21:56:54 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *b, size_t len)
{
	unsigned char	*ptrb;
	int				c;

	c = 0;
	ptrb = b;
	while (len--)
		*ptrb++ = (unsigned char)c;
}
