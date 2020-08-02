
#include "lem_in.h"


static void	save_flow(t_queue *q, t_lem_in *lem)
{
	int		e;
	int		s;

	e = END_ID;
	if (q->prev[e] == START_ID)
		return ;
	while (e != START_ID)
	{
		s = q->prev[e];
		//printf("R:%s\n", lem->id_table[s]->name);
		if (q->flow[e][s] == 0)
		{
			q->flow[e][s] = -1;
			q->flow[s][e] = 1;
		}
		else if (q->flow[e][s] == -1 || q->flow[e][s] == 1)
		{
			q->flow[e][s] = 0;
			q->flow[s][e] = 0;
		}
		e = s;
	}
}

int	back(t_queue *q, t_room *r)
{
	int x;
	int i;
	int j;
	
	j = 0;
	i = 0;
	x = -1;
	while (++x < r->links_nb)
	{
		if (q->flow[r->links[x]][r->id] == 1)
			j += 1;
		if (q->flow[r->id][r->links[x]] == 1)
			i += 1;
	}
	return (i == 1 && j == 1 ? 1 : 0);
}
			//&& rev != 1) || (rev == 1 && q->flow[r->links[i]][r->id] == 1
			//	&& q->visited[r->links[i]] != 1))

void	add_to_queue(t_queue *q, int room, int id)
{
	q->queue[q->position] = room;
	q->prev[room] = id;
	q->visited[room] = 1;
	++q->position;
}

static int	find_neg_flow(t_queue *q, t_room *r, t_lem_in *lem)
{
	int		i;
	int	n = 0;;

	i = 0;
	while (i < r->links_nb)
	{
		//printf(" %s ", lem->id_table[r->links[i]]->name);
		if (q->visited[r->links[i]] != 1 && q->flow[r->id][r->links[i]] == -1)
		{
			if (lem->id_table[r->links[i]]->weight != MAX_INT)
				check_dist(lem, q, r, lem->id_table[r->links[i]]);
			//printf("\tR%s", lem->id_table[r->links[i]]->name);
			//printf("addN(%d)", q->visited[r->links[i]]);
			q->queue[q->position] = r->links[i];
			q->prev[r->links[i]] = r->id;
			q->visited[r->links[i]] = 1;
			++q->position;
			lem->id_table[r->links[i]]->weight = r->weight - 1;
			return (1);
		}
		if (q->flow[r->links[i]][r->id] == 1)
			n = 1;
		++i;
	}
	return (n);
}


static int	find_flow(t_queue *q, t_room *r, int prev_flow, t_lem_in *lem)
{
	int		j;
	int n = 0;

	j = 0;
	//printf("\nName:%s(%d|%d)", r->name, q->visited[r->id], prev_flow);
	if (prev_flow == 0 && (n = find_neg_flow(q, r, lem)) == 1)
		return (0);
	while (j < r->links_nb)
	{
		//printf("\tR%2s", lem->id_table[r->links[j]]->name);
		if (lem->id_table[r->links[j]]->weight != MAX_INT)
			check_dist(lem, q, r, lem->id_table[r->links[j]]);
		if (q->visited[r->links[j]] != 1
			&& q->flow[r->id][r->links[j]] != 1
			&& (r->id != START_ID || r->links[j] != END_ID))
		{
			n += 1;
			//printf("addP(%d)", q->visited[r->links[j]]);
			q->queue[q->position] = r->links[j];
			q->prev[r->links[j]] = r->id;
			q->visited[r->links[j]] = 1;
			++q->position;
			if (q->flow[r->id][r->links[j]] == 0)
				lem->id_table[r->links[j]]->weight = r->weight + 1;
			else
				lem->id_table[r->links[j]]->weight = r->weight - 1;
		}
		//else
		//	printf("rem(%d)", q->visited[r->links[j]]);
		++j;
	}
	return (0);
}
static int	optimise_flow(t_lem_in *lem, t_queue *q, int *t)
{
	int		i;
	int		room;
	int		prev_flow;

	i = -1;
	prev_flow = 0;
	clear_queue(q);
	reset_queue(q, START_ID, END_ID);
	check_start_end(lem, q);
	while (++i < q->len && q->visited[END_ID] != 1 && q->queue[i] >= 0)
	{
		room = q->queue[i];
		i > 0 ? prev_flow = q->flow[q->prev[room]][room] : 0;
		find_flow(q, lem->id_table[room], prev_flow, lem);
	}
	//printf("\n");
	if (q->prev[END_ID] == -1 || (q->prev[END_ID] == START_ID && *t == 1))
		return (0);
	return (*t = 1);
}

void	path_find(t_lem_in *lem, t_queue *q, t_path **p)
{
	t_path	*new;

	int t = 0;
	*p = create_paths(NULL, 0);
	(*p)->llen = 0;
	set_max_weights(lem);
	while (optimise_flow(lem, q, &t))
	{
		new = create_paths(NULL, 0);
		new->llen = 0;
		save_flow(q, lem);
		reset_int_array(&q->visited, q->len, 0);
		reset_queue(q, lem->start->id, lem->end->id);
		save_paths(q, lem, &new);
		if ((*p)->llen == 0 || (*p)->llen > new->llen)
		{
			free_path((*p));
			*p = new;
		}
		else
			free_path(new);
		clear_queue(q);
	}
	t == 0 ? error_msg("No paths.\n") : 0;
}
