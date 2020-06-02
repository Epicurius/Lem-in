
#include "../lem_in.h"
#include <stdio.h>

int		path_length(t_lem_in *lem, t_link *link, int l)
{
	if (link == NULL)
		return (2147483647);
	if (link->end->bfs_val == 2147483647)
		return (l + 1);
	if (link->end->paths[0] == 0 && link->end != lem->end) //link->end->paths[0] > 1)
		return (2147483647);
	return (path_length(lem, find_link(lem, link->end, NULL), l + 1));
}

t_link		*find_optimal_rout(t_lem_in *lem, t_room *room)
{
	t_link *current;
	t_link *optimal;
	int min;
	int current_len;
	
	min = 2147483647;
	optimal = NULL;
	current = lem->links;
	while (current) //&& room->paths[1] > 1)
	{
		if (current->start == room && current->used != -1)
		{
			current_len = path_length(lem, current, 0);
			if (current_len < min)
			{
				min = current_len;
				optimal = current;
			}
		}
		current = current->next;
	}
	return (optimal);
}

void		trim_output(t_lem_in *lem)
{
	t_room	*current;
	t_link	*optimal;
	int x;

	optimal = NULL;
	x = lem->max_bfs;
	while (x > 0)
	{
		current = lem->rooms;
		while (current)
		{
			if (current->bfs_val == x && current->paths[1] > 1)
			{
				optimal = find_optimal_rout(lem, current);
				if (optimal != NULL)
					keep_optimal(lem, optimal, optimal->start, NULL);
			}
			current = current->next;
		}
		x--;
	}
	
}
