
#include "../lem_in.h"

int		is_end(t_lem_in *lem, t_link *link)
{
	if (link == NULL)
		return (0);
	if (link->end == lem->end)
		return (1);
	return (is_end(lem, find_link(lem, link->end, NULL)));
}

int	how_many_paths(t_lem_in *lem)
{
	t_link *current;
	int	used_paths;

	used_paths = 0;
	current = lem->links;
	while (current)
	{
		if (current->start == lem->start && current->used != -1)
		{
			//printf("Found 0 |");
			//if (is_end(lem, current) == 1)
			//{
			//	printf("Went to the end\n");
				used_paths += 1;
			//}
			//else
			//	printf("Dindnt end\n");
		}
		current = current->next;
	}
	if (used_paths < lem->max_rout)
	{
		if (last_chance(lem, lem->start) == 1)
			used_paths += 1;
		return (used_paths);
	}
	else
		return (used_paths);
}
