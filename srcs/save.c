/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:22:17 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 08:46:21 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	mark_path(t_lem_in *lem, t_queue *q)
{
	int	path;
	int	i;

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
	int	e;
	int	s;

	*steps = 0;
	s = START_ID;
	e = END_ID;
	while (e != s)
	{
		e = q->prev[e];
		++*steps;
	}
}

static int	*assign_path(t_lem_in *lem, t_queue *q)
{
	size_t	steps;
	int		*path;
	int		pos;
	int		i;

	i = -1;
	pos = END_ID;
	count_steps(q, &steps);
	path = ft_memalloc((sizeof(int)) * (steps + 1));
	if (!path)
		error_msg("Assign path malloc\n");
	while (++i <= steps)
	{
		path[steps - i] = pos;
		pos = q->prev[pos];
	}
	if (!path)
		error_msg("Cant find a single path.");
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
	reset_int_array(&q->visited, q->len, 0);
	while (bfs(lem, q))
	{
		path = assign_path(lem, q);
		count_steps(q, &steps);
		if (steps < s || s == 0)
			s = steps;
		mark_path(lem, q);
		tmp[nb].path = ft_memalloc((sizeof(int)) * (steps + 1));
		if (!tmp[nb].path)
			error_msg("Assign path malloc\n");
		ft_memcpy(tmp[nb].path, path, sizeof(int) * (steps + 1));
		tmp[nb].len = steps + 1;
		tmp[nb].div = 0;
		ft_memdel((void *)&path);
		nb += 1;
	}
	return (ant_algo(lem, nb, tmp, s));
}
