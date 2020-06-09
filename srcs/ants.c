/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 09:27:22 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 07:03:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	move_everyone(t_lem_in *lem)
{
	t_route *current;

	current = lem->routes;
	while (current)
	{
		reverse(lem, current);
		current = current->next;
	}
}

void	kickout_ant(t_lem_in *lem, t_route *route)
{
	if (route->strt->end == lem->end)
		lem->end->ants_in += 1;
	else
		route->strt->end->ants_in = lem->ant_name;
	ft_putstr("L");
	ft_putnbr(lem->ant_name);
	ft_putstr("-");
	ft_putstr(route->strt->end->name);
	ft_putstr(" ");
	lem->ant_name += 1;
}

void	move_from_start(t_lem_in *lem)
{
	t_route *current;

	current = lem->routes;
	while (current && lem->start->ants_in != 0)
	{
		if (lem->start->ants_in > ant_move_calc(lem, current))
		{
			kickout_ant(lem, current);
			lem->start->ants_in -= 1;
		}
		current = current->next;
	}
	ft_putstr("\n");
}

void	ant_algo(t_lem_in *lem)
{
	if (lem->enable_visuals == 2)
	{
		print_route(lem, 0);
		ft_putchar('\n');
	}
	while (lem->end->ants_in != lem->ants)
	{
		move_everyone(lem);
		move_from_start(lem);
	}
}
