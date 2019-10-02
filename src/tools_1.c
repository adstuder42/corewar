/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:59:00 by schabbi           #+#    #+#             */
/*   Updated: 2019/09/21 12:17:12 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int			mem_shift(short int shift, int pc, int long_addr)
{
	int		shift_s;
	int		shift_m;

	if (!long_addr)
	{
		shift_s = shift % IDX_MOD;
		if (shift_s < 0)
			shift = shift_s + MEM_SIZE;
		else
			shift = shift_s;
	}
	shift_m = ((pc + shift) % MEM_SIZE);
	if (shift_m < 0)
		shift_m = MEM_SIZE + shift_m;
	return (shift_m);
}

int			get_from_mem(int addr, int size, int mem[])
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < size)
	{
		ret += mem[addr + i];
		if (i != (size - 1))
			ret = ret << 8;
		i++;
	}
	return (ret);
}

t_process	*create_process(t_process *process, int pc
		, int player_master, t_data *data)
{
	t_process	*tmp;
	static	int	id = 0;

	if (!(tmp = malloc(sizeof(t_process))))
		return (NULL);
	data->c_dump = 1;
	data->p_arena[pc] = 1;
	ft_bzero(tmp->reg, sizeof(tmp->reg));
	tmp->player_master = player_master;
	tmp->reg[0] = player_master + 1;
	tmp->carry = 0;
	tmp->id = id;
	tmp->pc = pc;
	tmp->next = process;
	tmp->activation_countdown = 0;
	tmp->carry = 0;
	tmp->alive = 0;
	id++;
	return (tmp);
}

void		vm_err_player(char *msg, char *name)
{
	ft_printf("%s \"%s\"\n", msg, name);
	exit(EXIT_FAILURE);
}

int			check_prog_size(t_player *player, int i, char *argv)
{
	if (i == 0)
	{
		ft_printf("Faild reading the file : %s\n", argv);
		print_usage();
		return (0);
	}
	else if ((i - 16 - PROG_NAME_LENGTH - COMMENT_LENGTH) > CHAMP_MAX_SIZE)
		vm_err_player("Program size too large for player", player->name);
	else if (i <= 16 + PROG_NAME_LENGTH + COMMENT_LENGTH)
		vm_err_player("No program for player", player->name);
	return (1);
}
