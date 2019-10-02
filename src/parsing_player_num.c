/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 07:03:11 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/21 13:56:08 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int	parse_explicite_player_num(char *argv, t_data *data, t_player *player)
{
	if (ft_strlen(argv) > 2)
	{
		ft_printf("Player number must be an integer");
		ft_printf(" betwin 1 and 99\n");
		return (0);
	}
	data->parsing_state = NEXT_IS_ASM;
	if (!ft_isdigit(argv[0]) || ((argv[1]) & (!ft_isdigit(argv[1]))))
		return (err("Please chose a numerical player num"));
	player->num = ft_atoi(argv);
	if (data->assigned_player_nums[player->num - 1])
		return (err("you chosed an assigned player num"));
	data->assigned_player_nums[player->num - 1] = 1;
	if (player->num > 99 || player->num < 1)
	{
		ft_printf("Player number must be an integer");
		ft_printf(" betwin 1 and 99\n");
		return (0);
	}
	return (1);
}

int	define_player_num(t_data *data, t_player *player
		, char *argv, int player_num_explicite)
{
	int	i;

	i = -1;
	if (!player_num_explicite)
	{
		while (i++ <= 3)
			if (!data->assigned_player_nums[i])
			{
				data->assigned_player_nums[i] = 1;
				player->num = i + 1;
				data->parsing_state = IS_ASM;
				break ;
			}
	}
	else if (!parse_explicite_player_num(argv, data, player))
		return (0);
	return (1);
}
