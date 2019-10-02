/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:59:59 by xburelle          #+#    #+#             */
/*   Updated: 2018/11/28 22:31:52 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000
# include "libft.h"
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(const int fd, char **line);

#endif
