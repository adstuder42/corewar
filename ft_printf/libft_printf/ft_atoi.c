/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:41:32 by schabbi           #+#    #+#             */
/*   Updated: 2019/03/11 16:16:46 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int str_int;
	int n;
	int is_negativ;

	n = 0;
	is_negativ = 0;
	str_int = 0;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\v'
			|| str[n] == '\n' || str[n] == '\r' || str[n] == '\f')
		n++;
	if (str[n] == '+' || str[n] == '-')
		n++;
	if (n > 0)
		if (str[n - 1] == '-')
			is_negativ = 1;
	if (str[n] == '-' || str[n] == '+')
		return (0);
	while (str[n] >= '0' && str[n] <= '9')
	{
		str_int = (str_int * 10) + str[n] - 48;
		n++;
	}
	if (is_negativ)
		str_int *= (-1);
	return (str_int);
}
