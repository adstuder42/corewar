/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:40:47 by schabbi           #+#    #+#             */
/*   Updated: 2019/03/11 15:35:53 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	ft_wstrlen(const wchar_t *str, int precision)
{
	size_t	p;
	size_t	single_char_len;
	size_t	wstr_len;
	int		tmp_pr;

	tmp_pr = precision + 1;
	if (!str)
		return (0);
	p = 0;
	wstr_len = 0;
	while (str[p])
	{
		single_char_len = (count_bits(str[p], 2) == 17) ? 4
			: (count_bits(str[p], 2) / 6) + 1;
		tmp_pr -= single_char_len;
		if (precision)
			if (tmp_pr < 0)
				break ;
		wstr_len += single_char_len;
		p++;
	}
	return (wstr_len);
}
