
#include "./lem_in.h"

void	print_links(t_lem_in *lem)
{
	t_link *current;
	current = lem->links;
	while (current != NULL)
	{
		ft_putstr(current->start->name);
		ft_putchar('-');
		ft_putstr(current->end->name);
		ft_putchar('\n');
		current = current->next;
	}
}

void	print_room(t_lem_in *lem)
{
	t_room *current;
	current = lem->rooms;
	while (current != NULL)
	{
		if (current->type == START)
			ft_putstr("##start\n");
		else if (current->type == END)
			ft_putstr("##end\n");
		ft_putstr(current->name);
		ft_putchar(' ');
		ft_putnbr(current->yx[1]);
		ft_putchar(' ');
		ft_putnbr(current->yx[0]);
		ft_putchar('\n');
		current = current->next;
	}
}

void	print_route(t_lem_in *lem)
{
	t_route *current;
	t_link *current1;

	current = lem->routes;
	while (current != NULL)
	{
		current1 = current->strt;
		while (current1)
		{
			ft_putstr(current1->start->name);
			ft_putstr("->");
			if (!current1->next)
			{
				ft_putstr(current1->end->name);
			}
			current1 = current1->next;
		}
		ft_putstr("\n");
		current = current->next;
	}
}

void	print_map(t_lem_in *lem)
{
	ft_putnbr(lem->ants);
	ft_putstr("\n");
	print_room(lem);
	print_links(lem);	
	ft_putstr("\n");
}
