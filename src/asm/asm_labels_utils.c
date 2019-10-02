/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_labels_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:32:12 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 02:27:58 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_ptrcpy(char ***to, char **from)
{
	int		i;

	i = 0;
	while (from[i])
	{
		(*to)[i] = from[i];
		i++;
	}
	(*to)[i] = NULL;
}

void	asm_bigger_lab(t_data *data, char ***label, int nb)
{
	char	**tmp;

	if (!(tmp = (char **)malloc(sizeof(char *) * (nb + 1))))
	{
		asm_free_label(label);
		asm_memerr(data);
	}
	asm_ptrcpy(&tmp, *label);
	free(*label);
	if (!(*label = (char **)malloc(sizeof(char *) * (nb + 2))))
	{
		asm_free_label(&tmp);
		asm_memerr(data);
	}
	asm_ptrcpy(label, tmp);
	free(tmp);
}

void	asm_cpyto_nolab(t_data *data, char ***label, int *nb)
{
	if (!(data->inst->label = (char **)malloc(sizeof(char *) * (*nb + 1))))
	{
		asm_free_label(label);
		asm_memerr(data);
	}
	asm_ptrcpy(&(data->inst->label), *label);
	data->inst->label_bool = 1;
	free(*label);
	*nb = 0;
	*label = NULL;
}

void	asm_cpyto_inlinelab(t_data *data, char ***label, int *nb)
{
	asm_bigger_lab(data, label, *nb);
	(*label)[(*nb)++] = data->inst->label[0];
	(*label)[*nb] = NULL;
	free(data->inst->label);
	data->inst->label = NULL;
	if (!(data->inst->label = (char **)malloc(sizeof(char *) * (*nb + 2))))
	{
		asm_free_label(label);
		asm_memerr(data);
	}
	asm_ptrcpy(&(data->inst->label), *label);
	data->inst->label_bool = 1;
	free(*label);
	*nb = 0;
	*label = NULL;
}

void	asm_prepare_tmplab(t_data *data, char ***label, int nb)
{
	if (*label != NULL)
		asm_bigger_lab(data, label, nb);
	else
	{
		if (!(*label = (char **)malloc(sizeof(char *) * 2)))
			asm_memerr(data);
	}
}
