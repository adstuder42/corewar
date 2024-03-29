/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 12:01:47 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/11 14:19:06 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isprint(int c)
{
	if (c < 0 || c > 127)
		return (0);
	if ((unsigned char)c >= 32 && (unsigned char)c <= 126)
		return (1);
	else
		return (0);
}
