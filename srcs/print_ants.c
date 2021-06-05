/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:44:42 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/05 18:30:48 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static inline void	print_ant(long ant, char *room)
{
	write(1, "L", 1);
	ft_putnbr(ant);
	write(1, "-", 1);
	ft_putstr(room);
	write(1, " ", 1);
}

void	start_kick(t_lem_in *lem, int *name)
{
	int	i;

	i = 0;
	while (PATH[i].len != 0)
	{
		if (PATH[i].div > 0)
		{
			print_ant(*name, ID[PATH[i].path[1]]->name);
			ID[PATH[i].path[1]]->ant_id = *name;
			*name += 1;
			PATH[i].div -= 1;
		}
		i += 1;
	}
	write(1, "\n", 1);
}

void	move_along(t_lem_in *lem, int *end_ants)
{
	int	i;
	int	c;

	i = 0;
	while (lem->path_l.paths[i].len != 0)
	{
		c = lem->path_l.paths[i].len - 2;
		while (c > 0)
		{
			if (ID[PATH[i].path[c]]->ant_id != 0)
			{
				print_ant(ID[PATH[i].path[c]]->ant_id,
					ID[PATH[i].path[c + 1]]->name);
				ID[PATH[i].path[c + 1]]->ant_id = ID[PATH[i].path[c]]->ant_id;
				ID[PATH[i].path[c]]->ant_id = 0;
				if (ID[PATH[i].path[c + 1]]->id == END_ID)
					*end_ants += 1;
			}
			c -= 1;
		}
		i += 1;
	}
}

void	print_ants(t_lem_in *lem)
{
	int	name;
	int	end_ants;

	name = 1;
	end_ants = 0;
	while (end_ants < lem->ants)
	{
		move_along(lem, &end_ants);
		start_kick(lem, &name);
	}
}
