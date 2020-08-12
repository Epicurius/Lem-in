

#include "lem_in.h"

void	find_connected(t_queue *q, t_room *r)
{
	int	i;

	i = -1;
	t_list	*link;
	t_room 	*curr;

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
	int	i;
	t_list *link;

	i = -1;
	reset_int_array(&q->queue, q->len, -1);
	reset_queue(q, START_ID, END_ID);
	while (++i < q->len && q->visited[END_ID] != 1 && q->queue[i] >= 0)
		find_connected(q, lem->id_table[q->queue[i]]);
	if (q->visited[END_ID] != 1)
		return (0);
	if ((link = find_link(lem->start, END_ID)) != NULL)
	{
		if (link->content_size == 1 && q->prev[END_ID] == START_ID)
			link->content_size = 0;
	}
	return (1);
}
