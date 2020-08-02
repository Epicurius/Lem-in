

#include "lem_in.h"

void	find_connected(t_queue *q, t_room *r)
{
	int	i;

	i = -1;
	while (++i < r->links_nb)
		if (q->visited[r->links[i]] == 0 &&
			q->flow[r->id][r->links[i]] == 1)
			add_to_queue(q, r->links[i], r->id);
}

int	bfs(t_lem_in *lem, t_queue *q)
{
	int	i;

	i = -1;
	reset_int_array(&q->queue, q->len, -1);
	reset_queue(q, START_ID, END_ID);
	while (++i < q->len && q->visited[END_ID] != 1 && q->queue[i] >= 0)
		find_connected(q, lem->id_table[q->queue[i]]);
	if (q->visited[END_ID] != 1)
		return (0);
	if (q->flow[START_ID][END_ID] == 1 && q->prev[END_ID] == START_ID)
		q->flow[START_ID][END_ID] = 0;
	return (1);
}
