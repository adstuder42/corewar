/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:32:37 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/19 03:02:11 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_usage(void)
{
	ft_printf("\n\tASM - Usage\n\n"
		"\tCompile Core War champion file from .s to .cor where the result is "
		"in the same directory of <path/to/file.s>. \n\n"
		"\tasm <file.s>\n\n\n");
}
