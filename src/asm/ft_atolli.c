/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolli.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:32:44 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 02:29:43 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

long long int		ft_atolli(const char *str)
{
	int			i;
	long long	n;
	int			sign;

	i = 0;
	n = 0;
	sign = POSITIVE;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sign = NEGATIVE;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	if (sign == POSITIVE)
		return (n);
	else
		return (-n);
}
