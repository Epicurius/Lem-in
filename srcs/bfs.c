/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:48:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/05 17:52:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	find_connected(t_queue *q, t_room *r)
{
	int		i;
	t_list	*link;
	t_room	*curr;

	i = -1;
	link = r->link;
	while (link)
	{
		curr = link->content;
		if (q->visited[curr->id] == 0 && link->content_size == 1)
			add_to_queue(q, curr->id, r->id);
		link = link->next;
	}
}

int	bfs(t_lem_in *lem, t_queue *q)
{
	int		i;
	t_list	*link;

	i = -1;
	reset_int_array(&q->queue, q->len, -1);
	reset_queue(q, START_ID, END_ID);
	while (++i < q->len && q->visited[END_ID] != 1 && q->queue[i] >= 0)
		find_connected(q, lem->id_table[q->queue[i]]);
	if (q->visited[END_ID] != 1)
		return (0);
	link = find_link(lem->start, END_ID);
	if (link != NULL)
	{
		if (link->content_size == 1 && q->prev[END_ID] == START_ID)
			link->content_size = 0;
	}
	return (1);
}
