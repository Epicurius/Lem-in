/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 07:02:20 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 07:03:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		ant_move_calc(t_lem_in *lem, t_route *route)
{
	int		x;
	t_route	*current;

	x = 0;
	current = lem->routes;
	while (current != route)
	{
		x += (route->len - current->len);
		current = current->next;
	}
	return (x);
}

void	reverse(t_lem_in *lem, t_route *route)
{
	t_link	*current;

	current = route->strt;
	while (current->next)
		current = current->next;
	while (current && current->start != lem->start)
	{
		if (current->start->ants_in != 0)
		{
			ft_putstr("L");
			ft_putnbr(current->start->ants_in);
			ft_putstr("-");
			ft_putstr(current->end->name);
			ft_putstr(" ");
		}
		if (current->end == lem->end && current->start->ants_in != 0)
			lem->end->ants_in += 1;
		else if (current->end != lem->end)
			current->end->ants_in = current->start->ants_in;
		current->start->ants_in = 0;
		current = current->prev;
	}
}
