
#include "../lem_in.h"
#include <stdio.h>

int		last_chance(t_lem_in *lem, t_room *room)
{
	t_link *current;

	current = lem->links;
	while (current)
	{
		if (current->used == -1 && current->start == room)
		{
			current->used = 0;
			current->start->paths[1] += 1;
			current->end->paths[0] += 1;
			if (current->end == lem->end)
				return (1);
			if (last_chance(lem, current->end) == 1)
				return (1);
			else
			{
				current->used = -1;
				current->start->paths[1] -= 1;
				current->end->paths[0] -= 1;
			}
		}
		current = current->next;
	}
	return (0);
}

void		clean(t_lem_in *lem)
{
	t_link	*current;
	t_link	*remove;

	current = lem->links;
	while (current)
	{
		remove = current;
		current = current->next;
		if (remove->used == -1)
			delet(lem, remove);
	}
}
