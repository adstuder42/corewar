/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:41:46 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/19 07:54:53 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

long int	vm_abs(long int *nb)
{
	int		neg;

	neg = 0;
	if (*nb < 0)
	{
		*nb *= -1;
		neg = 1;
	}
	return (neg);
}

void		vm_negsign(long int *nb, int neg)
{
	if (neg)
		*nb *= -1;
}

int			is_player(int i, int buf)
{
	const	int	magic[4] = {0, 234, 131, 243};

	if (i < 4 && magic[i] != buf)
		return (0);
	return (1);
}

void		set_aliveprocess(t_data *data, int i, int set)
{
	t_process	*process;

	process = data->init_process[i];
	while (process)
	{
		process->alive = set;
		process = process->next;
	}
	data->nb_process_lives = 0;
}

void		vm_process_die(t_data *data, int i)
{
	t_process	*process;
	t_process	*tmp;
	t_process	*prev;

	process = data->init_process[i];
	while (process)
	{
		if (process->alive == 0)
		{
			tmp = process->next;
			if (process == data->init_process[i] && process->next != NULL)
				data->init_process[i] = process->next;
			else if (process == data->init_process[i])
				data->init_process[i] = NULL;
			else
				prev->next = tmp;
			data->p_arena[process->pc] = 0;
			free(process);
			process = tmp;
			continue ;
		}
		prev = process;
		process = process->next;
	}
}
