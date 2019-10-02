/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:10:41 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/11 14:16:42 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalpha(int c)
{
	if (c < 0 || c > 127)
		return (0);
	if (((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')
			|| ((unsigned char)c >= 'a' && (unsigned char)c <= 'z'))
		return (1);
	else
		return (0);
}
