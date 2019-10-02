/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:04:03 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/12 19:11:21 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*res;

	res = NULL;
	if (content == NULL)
	{
		if (!(res = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		if (!(res = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		res->content = (void *)ft_memalloc(content_size);
		ft_memcpy(res->content, content, content_size);
		res->content_size = content_size;
	}
	res->next = NULL;
	return (res);
}
