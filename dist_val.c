
#include "lem_in.h"

//call dist

void	set_max_weights(t_lem_in *lem)
{
	int x;

	x = 0;
	while (x < lem->room_nb)
		lem->id_table[x++]->weight = MAX_INT;
	lem->start->weight = 0;
}

static int	if_next_bfs_lower(t_room *next, t_room *curr, t_queue *q)
{
	int pos;

	if (q->flow[curr->id][next->id] == 1)
		return (1);
	if (q->flow[curr->id][next->id] == -1)
		pos = curr->weight - 1;
	else
		pos = curr->weight + 1;
	if (pos < next->weight && next->weight != MAX_INT)
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
	if ((lem->id_table[q->prev[next->id]] != lem->start) &&
		(!if_loop(lem, lem->id_table[q->prev[next->id]], next, q)) &&
		(!if_next_bfs_lower(lem->id_table[q->prev[next->id]], next, q)))
	{
		//printf("{Y}");
		q->prev[q->prev[next->id]] = next->id;
	}
	//printf("{N}");
	q->prev[next->id] = curr->id;
}
