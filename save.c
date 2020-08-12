
#include "lem_in.h"

static void		mark_path(t_lem_in *lem, t_queue *q)
{
	int		path;
	int		i;

	i = -1;
	path = q->prev[END_ID];
	while (path != START_ID)
	{
		q->visited[path] = 2;
		path = q->prev[path];
	}
	while (++i < q->len)
	{
		q->prev[i] = -1;
		q->queue[i] = -1;
		if (q->visited[i] == 1)
			q->visited[i] = 0;
	}
}


void	count_steps(t_queue *q, size_t *steps)
{
	int		e;
	int		s;

	*steps = 0;
	s = START_ID;
	e = END_ID;
	while (e != s)
	{
		e = q->prev[e];
		++*steps;
	}
}

static int		*assign_path(t_lem_in *lem, t_queue *q)
{
	size_t		steps;
	int		*path;
	int		pos;
	int		i;

	i = -1;
	pos = END_ID;
	count_steps(q, &steps);
	if (!(path = ft_memalloc((sizeof(int)) * (steps + 1))))
		error_msg("Assign path malloc\n");
	while (++i <= steps)
	{
		path[steps - i] = pos;
		pos = q->prev[pos];
	}
	return (path);
}

int	save_paths(t_queue *q, t_lem_in *lem, t_path *tmp)
{
	size_t	steps;
	int		*path;
	int		nb;
	int		s;
	
	nb = 0;
	s = 0;
	lem->start->weight = 0;
	reset_int_array(&q->visited, q->len, 0);
	while (bfs(lem, q))
	{
		if (!(path = assign_path(lem, q)))
			error_msg("Cant find a single path.");
		count_steps(q, &steps);
		(steps < s || s == 0) ? s = steps : 0;
		mark_path(lem, q);
		if (!(tmp[nb].path = ft_memalloc((sizeof(int)) * (steps + 1))))
			error_msg("Assign path malloc\n");
		ft_memcpy(tmp[nb].path, path, ((steps + 1) * sizeof(int)));
		tmp[nb].len = steps + 1;
		tmp[nb].div = 0;
		ft_memdel((void*)&path);
		nb += 1;
	}
	return (ant_algo(lem, nb, tmp, s));
}
