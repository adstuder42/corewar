/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:38:31 by schabbi           #+#    #+#             */
/*   Updated: 2018/10/27 01:40:17 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

uintmax_t	ft_power(uintmax_t nbr1, uintmax_t nbr2)
{
	uintmax_t	tmp;

	tmp = nbr1;
	while (nbr2 > 1)
	{
		nbr1 *= tmp;
		nbr2--;
	}
	return (nbr1);
}
