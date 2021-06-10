/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:29:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 16:52:19 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	print_flows(t_lem_in *lem, t_path *tmp, int path_nb, int moves)
{
	int	i;

	i = -1;
	ft_dprintf(2, "{CYAN}~~~~~~~~~~~~~~~~~~ %2d ~~~~~~~~~~~~~~~~~~{RESET}\n", moves);
	while (++i < path_nb)
	{
		ft_dprintf(2, "%d:\t%d[%d]\n", i, tmp[i].len - 1, tmp[i].div);
	}
	ft_dprintf(2, "{CYAN}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{RESET}\n");
}

void	print_check(t_lem_in *lem)
{
	ft_dprintf(2, "{GREEN}==================INFO=================={RESET}\n");
	if (lem->min_moves != NULL)
	{
		ft_dprintf(2, "%s\n", lem->min_moves);
		free(lem->min_moves);
	}
	ft_dprintf(2, "\tMoves:\t\t%d\n", lem->path_l.moves);
	ft_dprintf(2, "\tAnts:\t\t%d\n", lem->ants);
	ft_dprintf(2, "\tRooms:\t\t%d\n", lem->room_nb);
	ft_dprintf(2, "\tLinks:\t\t%d\n", lem->links_nb);
	ft_dprintf(2, "{GREEN}========================================{RESET}\n");
}

void	print_queue(t_lem_in *lem, t_queue *q, int i)
{
	int	x;

	x = -1;
	while (++x < q->position)
	{
		if (x == i)
			ft_dprintf(2, "{CYAN}[%s]{RESET}", lem->id_table[q->queue[x]]->name);
		else
			ft_dprintf(2, "%s", lem->id_table[q->queue[x]]->name);
		if (x + 1 != q->position)
			ft_dprintf(2, "-");
	}
	ft_dprintf(2, "\n");
}
