#include "./lem_in.h"
#include <stdio.h>

int		ant_move_calc(t_lem_in *lem, t_path *paths, t_path *path)
{
	int x;
	t_path *curr;

	x = 0;
	curr = paths;
	while (curr != path)
	{
		x += (path->len - curr->len);
		curr = curr->next;
	}
	return (x);
}

void		move_from_start(t_lem_in *lem, t_path *paths, int *ants)
{
	t_path *curr;

	curr = paths;
	while (curr && *ants > 0)
	{
		if (*ants > ant_move_calc(lem, paths, curr))
		{
			*ants -= 1;
			curr->move += 1;
		}
		curr = curr->next;
	}
}

int s_p(t_path *paths)
{
	t_path *curr;
	int shortest = MAX_INT;

	curr = paths;
	//printf("Lenghts: ");
	while (curr)
	{
		//printf("%d ", curr->len);
		if (curr->len < shortest)
			shortest = curr->len;
		curr = curr->next;
	}
	return (shortest);
}

void	print_flows(t_lem_in *lem, t_path *paths)
{
	int i;
	int j;
	t_path *curr;

	curr = paths;
	i = -1;
	j = 1;
	printf("~~~~~~~~~~~~~~~~~~~~~~ %2d ~~~~~~~~~~~~~~~~~~~~~~\n", paths->llen);
	while (curr != NULL)
	{
		printf("%2d: %d(%d)\n", j, curr->len, curr->move);
		//printf("%2d: %d(%d)\t", j, curr->len, curr->move);
		//int k = -1;
		//while (++k < curr->len + 1)
		//	printf("%s->", lem->id_table[curr->path[k]]->name);
		//printf("\n");
		j++;
		curr = curr->next;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void		ant_algo(t_lem_in *lem, t_path *paths)
{
	int max_ants;
	int shortest = s_p(paths);

	max_ants = lem->ants;
	//printf("Shortest: %d max_ants%d\n", shortest, max_ants);
	int c = 0;
	while (max_ants > 0)
	{
		c += 1;
		move_from_start(lem, paths, &max_ants);
	}
	c += shortest - 1;	
	paths->llen = c;
	//print_flows(lem, paths);
	//printf("\np->llen: %d\n", paths->llen);
}
