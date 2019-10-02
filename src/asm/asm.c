/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:27:50 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/21 12:15:19 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Global variables
*/
t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

void	asm_cpyto_tmplab(t_data *data, char ***label, int *nb)
{
	t_inst	*tmp;

	asm_prepare_tmplab(data, label, *nb);
	(*label)[(*nb)++] = data->inst->label[0];
	(*label)[*nb] = NULL;
	free(data->inst->label);
	data->inst->label = NULL;
	if ((tmp = data->inst->next) != NULL)
		asm_delone_inst(data, &(data->first_inst), data->inst);
	else
	{
		data->inst->opc = 16;
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
	data->inst = tmp;
}

void	asm_manage_labels(t_data *data)
{
	char			**label;
	int				nb;

	data->first_inst = data->inst;
	label = NULL;
	nb = 0;
	while (data->inst != NULL)
	{
		if (label != NULL && data->inst->label_bool == 0)
			asm_cpyto_nolab(data, &label, &nb);
		else if (label != NULL && data->inst->label_bool == 1)
			asm_cpyto_inlinelab(data, &label, &nb);
		if (data->inst->label_bool == 2)
		{
			asm_cpyto_tmplab(data, &label, &nb);
			continue ;
		}
		data->inst = data->inst->next;
	}
	data->inst = data->first_inst;
}

void	asm_asm(int fd, t_data *data)
{
	data->nb_name_prog = 0;
	data->nb_comment_prog = 0;
	data->raw_header = NULL;
	data->head_type = 0;
	data->inst = NULL;
	data->first_inst = NULL;
	data->label_call = NULL;
	asm_read(fd, data);
	asm_manage_labels(data);
	data->nb_bytes = 0;
	data->write = 0;
	asm_wtranslation(data, g_op_tab);
	asm_free_header(data->raw_header);
	asm_free_insts(data->inst);
	close(data->fd);
}

int		main(int ac, char **av)
{
	char	*fbasename;
	t_data	data;

	if (ac != 2)
	{
		asm_usage();
		return (EXIT_FAILURE);
	}
	if (!ft_isext(av[1], ".s"))
		asm_err("Wrong file extension");
	if ((data.fdin = open(av[1], O_RDONLY)) == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	if (!(fbasename = ft_basename(av[1])))
		asm_memerr3();
	data.fnameout = ft_strjoin(fbasename, ".cor");
	free(fbasename);
	asm_asm(data.fdin, &data);
	close(data.fdin);
	free(data.fnameout);
	return (EXIT_SUCCESS);
}
