/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:29:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/08 19:31:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	print_flows(t_lem_in *lem, t_path *tmp, int path_nb, int moves)
{
	int	i;

	i = 0;
	ft_putstr("~~~~~~~~~~~~~~~~~~ ");
	ft_putnbr(moves);
	ft_putstr(" ~~~~~~~~~~~~~~~~~~\n");
	while (i < path_nb)
	{
		ft_putnbr(i);
		ft_putstr(":\t");
		ft_putnbr(tmp[i].len - 1);
		write(1, "[", 1);
		ft_putnbr(tmp[i].div);
		ft_putstr("]\n");
		i++;
	}
	ft_putstr("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void	print_check(t_lem_in *lem)
{
	ft_printf("{GREEN}==================INFO=================={RESET}\n");
	ft_printf("\tMoves:\t%d\n", lem->path_l.moves);
	ft_printf("\tAnts:\t%d\n", lem->ants);
	ft_printf("\tRooms:\t%d\n", lem->room_nb);
	ft_printf("\tLinks:\t%d\n", lem->links_nb);
	ft_printf("{GREEN}========================================{RESET}\n");
}

void	print_queue(t_lem_in *lem, t_queue *q, int i)
{
	int	x;

	x = -1;
	while (++x < q->position)
	{
		if (x == i)
			write(1, "[", 1);
		ft_putstr(lem->id_table[q->queue[x]]->name);
		if (x == i)
			write(1, "]", 1);
		if (x + 1 != q->position)
			write(1, "-", 1);
	}
	write(1, "\n", 1);
}
