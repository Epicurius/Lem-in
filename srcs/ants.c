
#include "../lem_in.h"
#include <stdio.h>

int		ant_move_calc(t_lem_in *lem, t_route *route)
{
	int x;
	t_route *current;

	x = 0;
	current = lem->routes;
	while (current != route)
	{
		x += (route->len - current->len);
		current = current->next;
	}
	return (x);
}

void 	reverse(t_lem_in *lem, t_route *route)
{
	int	prev_name;
	int	tmp;
	t_link	*current;

	prev_name = 0;
	current = route->strt;
	while (current->next)
		current = current->next;
	while (current)
	{
		tmp = current->start->ants_in;
		if (tmp != 0)// || tmp == 0)
		{
			ft_putstr("L");
			ft_putnbr(tmp);
			ft_putstr("-");
			ft_putstr(current->end->name);
			ft_putstr(" ");
		}
		if (current->end == lem->end && tmp != 0)
			lem->ants_end += 1;
		else
			current->end->ants_in = tmp;
		current = current->prev;
	}
}

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
		lem->ants_end += 1;
	else
		route->strt->end->ants_in = lem->ant_name;
	ft_putstr("L");
	ft_putnbr(lem->ant_name);
	ft_putstr("-");
	ft_putstr(route->strt->end->name);
	ft_putstr(" ");
	lem->ant_name += 1;
}

void		move_from_start(t_lem_in *lem)
{
	t_route *current;

	current = lem->routes;
	while (current && lem->ants != 0)
	{
		if (lem->ants > ant_move_calc(lem, current))
		{
			kickout_ant(lem, current);
			lem->ants -= 1;
		}
		current = current->next;
	}
	ft_putstr("\n");
}

void		ant_algo(t_lem_in *lem)
{
	int max_ants;
	
	lem->ant_name = 1;	
	max_ants = lem->ants;
	lem->ants_end = 0;
	while (lem->ants_end != max_ants)
	{
		move_everyone(lem);
		move_from_start(lem);	
	}
}
