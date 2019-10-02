/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:33:18 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 02:47:17 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_isext(char *s, char *type)
{
	char	*ptr;

	ptr = ft_strstr(s, type);
	if (ptr == NULL)
		return (0);
	else if (*ptr == *type)
		return (1);
	return (0);
}
