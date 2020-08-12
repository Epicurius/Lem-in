/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:29:44 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/12 17:29:47 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	if_next_bfs_lower(t_room *next, t_room *curr, t_queue *q)
{
	int pos;
	int nw;
	t_list *link;

	link = find_link(curr, next->id);
	if (link->content_size == 1)
		return (1);
	if (link->content_size == -1)
		pos = curr->weight - 1;
	else
		pos = curr->weight + 1;
	if (pos < next->weight && q->visited[next->id] == 0)
	{
		next->weight = pos;
		return (0);
	}
	return (1);
}

static int	if_loop(t_lem_in *lem, t_room *curr, t_room *next, t_queue *q)
{
	int i;

	i = q->prev[curr->id];
	while (i != END_ID && i != START_ID)
	{
		if (i == next->id || i == curr->id || i == q->prev[next->id])
			return (1);
		i = q->prev[i];
	}
	return (0);
}

void	check_dist(t_lem_in *lem, t_queue *q, t_room *curr, t_room *next)
{
	if (next->id == START_ID || curr->id == START_ID || next == curr)
		return ;
	if (if_loop(lem, curr, next, q) || if_next_bfs_lower(next, curr, q))
		return ;
	if (lem->id_table[q->prev[next->id]] != lem->start)
		if (!if_loop(lem, lem->id_table[q->prev[next->id]], next, q))
			if (!if_next_bfs_lower(lem->id_table[q->prev[next->id]], next, q))
				q->prev[q->prev[next->id]] = next->id;
	q->prev[next->id] = curr->id;
}
