/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:32:32 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 19:42:02 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_check_comma(char *line, int nu, t_data *data)
{
	int		i;
	char	*ptr;
	int		len;
	char	*ptr2;

	len = ft_strlen(line);
	if (len != 0 && line[len - 1] == ',')
	{
		if (!ft_strchr(line, '#') && !ft_strchr(line, ';'))
			asm_handle_error(data, nu, len - 1, "SEPARATOR \",\"");
	}
	if (len != 0 && (ptr = ft_strstr(line, ",,")))
	{
		ptr2 = line;
		i = 0;
		while (ptr2++ != ptr)
			i++;
		if (!ft_strnstr(line, "#", i) && !ft_strnstr(line, ";", i))
			asm_handle_error(data, nu, asm_err_col(line, ptr),
				"SEPARATOR \",\"");
	}
}

int		asm_lexer_browse(char *line, int nu, t_data *data)
{
	char	**split_line;
	int		i;
	int		head_type;

	if ((head_type = asm_is_prog_head(data, line)) != -1)
		if (asm_parse_header(data, line, nu, head_type) != -1)
			return (1);
	asm_check_comma(line, nu, data);
	if (!(split_line = ft_bstrsplit2(line, DELIMITER)))
		asm_memerr(data);
	asm_parse(data, split_line, nu, line);
	i = 0;
	while (split_line[i])
		free(split_line[i++]);
	if (split_line != NULL)
		free(split_line);
	return (1);
}

int		asm_create_ast(char *line, int *nu, t_data *data)
{
	if (asm_lexer_browse(line, *nu, data) == -1)
		return (FALSE);
	(*nu)++;
	return (1);
}

void	asm_read(int fd, t_data *data)
{
	int			ret;
	char		*line;
	int			i;

	i = 1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (asm_create_ast(line, &i, data) == FALSE)
			break ;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
}
