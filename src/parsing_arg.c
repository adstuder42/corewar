/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 02:22:32 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/21 13:57:28 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"
#include <limits.h>

int		parsing(char **argv, int argc, t_data *dt, t_player *players)
{
	int			i;
	static	int	p;

	p = 0;
	i = 1;
	while (i < argc)
	{
		if (!parse_no_asm_arg(dt, players + p, argv[i], p))
			return (0);
		define_nbr_players(dt, i, argc, argv);
		if (dt->nbr_of_players > 4)
			return (err("it can't be more than 4 wariors in the same arena !"));
		if (dt->parsing_state == IS_ASM || dt->parsing_state == DEFAULT_STATE)
		{
			if (!parse_asm_arg(argv[i], players + p, dt, dt->nbr_of_players))
				return (0);
			if (ft_strstr(argv[i], ".cor"))
				p++;
		}
		if (dt->parsing_state == IS_ASM || dt->parsing_state == RESET_DEFAULT)
			dt->parsing_state = DEFAULT_STATE;
		i++;
	}
	return (1);
}

void	define_nbr_players(t_data *data, int i, int argc, char **argv)
{
	static	int	defined = 0;
	int			j;

	j = i;
	if (!defined)
	{
		if (data->parsing_state == IS_ASM)
		{
			while (j < argc)
			{
				if (!ft_strcmp(argv[j], "-n")
						|| (!ft_strcmp(argv[j], "-dump"))
						|| (!ft_strcmp(argv[j], "-v")))
					j++;
				else
				{
					if (ft_strstr(argv[j], ".cor"))
						data->nbr_of_players++;
					j++;
				}
			}
			defined = 1;
		}
	}
}

int		define_nbr_cycle(t_data *data, char *argv)
{
	static	int	defined = 0;

	if (defined)
		return (err("Number of cycle can not be defined more than once"));
	defined = 1;
	data->parsing_state = RESET_DEFAULT;
	data->nbr_cycles = ft_atoi(argv);
	if (data->nbr_cycles < 1)
	{
		ft_printf("Number of cycle for dumping must be an integer");
		ft_printf(" bigger than one\n");
		return (0);
	}
	return (1);
}

int		parse_no_asm_arg(t_data *data, t_player *player, char *argv, int p)
{
	if (data->parsing_state == NEXT_IS_ASM)
		return ((data->parsing_state = IS_ASM));
	if (data->parsing_state == NEXT_IS_NBR_CYCLE)
		return (define_nbr_cycle(data, argv));
	if (!ft_strcmp(argv, "-dump"))
	{
		if (data->parsing_state == NEXT_IS_PLAYER_NUM)
			return (err("please chose a numerical player number !"));
		return (data->parsing_state = NEXT_IS_NBR_CYCLE);
	}
	if (!ft_strcmp(argv, "-v"))
	{
		data->vis = 1;
		return (data->parsing_state = VISU_REQ);
	}
	if (!ft_strcmp(argv, "-n"))
		return ((data->parsing_state = NEXT_IS_PLAYER_NUM));
	if (data->parsing_state == NEXT_IS_PLAYER_NUM)
	{
		if ((p > 3) || !define_player_num(data, player, argv, 1))
			return (err("Player number error !"));
	}
	else
		define_player_num(data, player, argv, 0);
	return (1);
}
