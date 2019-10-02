/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 02:17:04 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 04:21:16 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int	print_usage(void)
{
	ft_printf("usage:\n");
	ft_printf("./corewar [-v] [-dump nbr_cycles]");
	ft_printf(" [[-n number] champion1.cor] ...\n");
	return (0);
}

int	err(char *msg)
{
	ft_printf("%s\n", msg);
	return (0);
}

int	mem_dump(int arena[MEM_SIZE])
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", arena[i]);
		i++;
		j++;
		if (j == 64)
		{
			j = 0;
			ft_printf("\n");
		}
	}
	return (1);
}
