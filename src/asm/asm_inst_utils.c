/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_inst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:31:43 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:31:44 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_delone_inst(t_data *data, t_inst **insts, t_inst *todel)
{
	t_inst	*first;

	first = *insts;
	if (*insts == todel)
	{
		*insts = (*insts)->next;
		data->first_inst = *insts;
		free(todel);
		return ;
	}
	while ((*insts)->next != todel)
		*insts = (*insts)->next;
	(*insts)->next = todel->next;
	free(todel);
	*insts = first;
}
