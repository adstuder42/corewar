/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:09:46 by xburelle          #+#    #+#             */
/*   Updated: 2018/04/16 14:09:55 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list			*res;
	t_list			*el;
	t_list			*res1;

	if (lst == NULL || f == NULL)
		return (NULL);
	el = f(lst);
	if (!(res = ft_lstnew(el->content, el->content_size)))
		return (NULL);
	res1 = res;
	lst = lst->next;
	while (lst != NULL)
	{
		el = f(lst);
		if (!(res->next = ft_lstnew(el->content, el->content_size)))
			return (NULL);
		res = res->next;
		lst = lst->next;
	}
	return (res1);
}
