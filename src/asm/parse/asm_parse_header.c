/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:37:56 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 00:57:28 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_head_quotes(t_data *data, t_head *head, char *line, int *i)
{
	if (i[2] == 1 && i[1] - i[0] > PROG_NAME_LENGTH)
		asm_handle_error(data, i[3], 0, "Champion name too long "
			"(Max length 128)");
	else if (i[2] == 2 && i[1] - i[0] > COMMENT_LENGTH)
		asm_handle_error(data, i[3], 0, "Champion comment too long "
			"(Max length 2048)");
	if (data->head_type > 0)
		head = data->raw_header;
	else
		asm_init_head(data, &head);
	head->type = i[2] == 1 ? prog_name_exp : prog_comment_exp;
	if (i[2] == 1)
		data->nb_name_prog++;
	else if (i[2] == 2)
		data->nb_comment_prog++;
	ft_strncat(head->val, line + i[0], i[1] - i[0]);
	if (data->head_type == 0)
		asm_add_head(&(data->raw_header), head);
	data->head_type = 0;
	asm_comment_afterhead(data, line, i);
	return (1);
}

int		asm_head_eol(t_data *data, t_head *head, char *line, int *i)
{
	if (data->head_type > 0)
		head = data->raw_header;
	else
		asm_init_head(data, &head);
	if (i[2] == 1
	&& ft_strlen(head->val) + i[1] + 1 - i[0] <= PROG_NAME_LENGTH)
		ft_strncat(head->val, line + i[0], i[1] - i[0]);
	else if (i[2] == 2
	&& ft_strlen(head->val) + i[1] + 1 - i[0] <= COMMENT_LENGTH)
		ft_strncat(head->val, line + i[0], i[1] - i[0]);
	else if (i[2] == 1)
		asm_handle_error(data, i[3], 0, "Champion name too long "
			"(Max length 128)");
	else if (i[2] == 2)
		asm_handle_error(data, i[3], 0, "Champion comment too long "
			"(Max length 2048)");
	ft_strcat(head->val, "\n");
	if (data->head_type == 0)
		asm_add_head(&(data->raw_header), head);
	data->head_type = i[2];
	return (1);
}

void	asm_prepare_header_parsing(t_data *data, int *i, char *line,
			t_head **first)
{
	int		j;

	j = 0;
	if (data->nb_name_prog > 1 || data->nb_comment_prog > 1)
		asm_handle_error(data, i[3], 0, "Name or comment program must be "
			"declared 1 time");
	if (data->head_type > 0)
	{
		i[2] = data->head_type;
		i[0] = 0;
	}
	else
	{
		while (line[j] != '\0' && ft_strchr(" \t", line[j]))
			j++;
		i[0] = i[2] == 1 ? 5 + j : 8 + j;
		while (line[i[0]] != '\0' && ft_strchr(" \t", line[i[0]]))
			i[0]++;
	}
	*first = data->raw_header;
	if (data->raw_header != NULL)
		while (data->raw_header->next != NULL)
			data->raw_header = data->raw_header->next;
}

void	asm_parse_head_content(t_data *data, t_head *head, char *line, int *i)
{
	while (line[i[1]] != '\0' && line[i[1]] != '\"')
		i[1]++;
	if (line[i[1]] == '\"')
		asm_head_quotes(data, head, line, i);
	else if (line[i[1]] == '\0')
		asm_head_eol(data, head, line, i);
	else
		asm_handle_error(data, i[3], i[0], "Missing closing double quotes for "
			"program name or comment");
}

int		asm_parse_header(t_data *data, char *line, int nu, int head_type)
{
	int		i[4];
	t_head	*head;
	t_head	*first;

	head = NULL;
	i[3] = nu;
	i[2] = head_type;
	asm_prepare_header_parsing(data, i, line, &first);
	if (data->head_type > 0)
	{
		i[1] = i[0];
		asm_parse_head_content(data, head, line, i);
	}
	else if (line[i[0]] == '\"')
	{
		i[1] = ++i[0];
		asm_parse_head_content(data, head, line, i);
	}
	else
		asm_handle_error(data, i[3], i[0], "Missing opening double quotes for "
			"program name or comment");
	if (first != NULL)
		data->raw_header = first;
	return (1);
}
