
#include "../lem_in.h"
#include <stdio.h>

t_link		*find_link(t_lem_in *lem, t_room *s, t_room *e)
{
	t_link *current;

	current = lem->links;
	while (current)
	{
		if (((s && current->start == s) || (e && current->end == e))
				&& current->used != 1)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int		reaches_start(t_lem_in *lem, t_link *link)
{
	if (link->start == lem->start)
		return (0);
	if (link->start->paths[1] > 1)
		return (1);
	return (reaches_start(lem, find_link(lem, NULL, link->start)));
}

void		find_optimal_fork(t_lem_in *lem, t_room *room)
{
	t_link *current;
	t_link *optimal;

	optimal = NULL;
	current = lem->links;
	while (current && room->paths[0] > 1)
	{
		optimal = current;
		current = current->next;
		if (optimal->end == room && optimal->used != -1)
		{
			if (reaches_start(lem, optimal) == 0)
				keep_optimal(lem, optimal, NULL, optimal->end);
			else
				delet(lem, optimal);
		}
	}
}

void		trim_input(t_lem_in *lem)
{
	t_room	*current;
	int	x;

	x = 1;
	while (x <= lem->max_bfs)
	{
		current = lem->rooms;
		while (current)
		{
			if (current->bfs_val == x && current->paths[0] > 1)
				find_optimal_fork(lem, current);
			current = current->next;
		}
		x++;
	}

}
