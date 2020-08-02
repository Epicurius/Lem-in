
#include "lem_in.h"

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

static void		mark_path(t_lem_in *lem, t_queue *q)
{
	int		path;
	int		i;

	i = -1;
	path = q->prev[END_ID];
	while (path != START_ID)
	{
		q->visited[path] = 2; // 2
		path = q->prev[path];
	}
	while (++i < q->len)
	{
		q->prev[i] = -1;
		q->queue[i] = -1;
		if (q->visited[i] == 1) // 1
			q->visited[i] = 0;
	}
}

t_path	*create_paths(int *path, int len)
{
	t_path *new;

	if (!(new = ft_memalloc(sizeof(t_path) + (sizeof(int) * (len + 1)))))
		error_msg("Creating path list malloc.");
	if (path != NULL)
	{
		if (!(new->path = ft_memalloc(sizeof(int) * (len + 1))))
			error_msg("Creating a path malloc.");
		ft_memcpy(new->path, path, ((len) * sizeof(int)));
		new->len = len - 1;
	}
	else
	{
		new->path = NULL;
		new->len = 0;
	}
	new->next = NULL;
	new->div = NULL;
	new->move = 0;
	return (new);
}

void	save_paths(t_queue *q, t_lem_in *lem, t_path **path_l)
{
	int	*path;
	size_t	steps;
	t_path	*new;
	int	paths_nb;

	paths_nb = 0;
	set_max_weights(lem);
	while (bfs(lem, q))
	{
		if (!(path = assign_path(lem, q)))
			error_msg("Cant find a single path.");
		count_steps(q, &steps);
		mark_path(lem, q);
		if (!(new = create_paths(path, steps + 1)))
			error_msg("Cant find a single path.");
		free(path); //memdel
		add_path_to_list(*path_l, new);
		paths_nb += 1;
	}
	set_path(path_l, paths_nb, lem);
}
