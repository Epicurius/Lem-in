
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

void	add_to_queue(t_queue *q, int room, int id)
{
	q->queue[q->position] = room;
	q->prev[room] = id;
	q->visited[room] = 1;
	++q->position;
}

static int	find_neg_flow(t_queue *q, t_room *r, t_lem_in *lem)
{
	int		n = 0;
	t_list		*link;
	t_room		*curr;

	link = r->link;
	while (link)
	{
		curr = link->content;
		if (q->visited[curr->id] != 1 && q->flow[r->id][curr->id] == -1)
		{
			if (curr->weight != MAX_INT)
				check_dist(lem, q, r, curr);
			add_to_queue(q, curr->id, r->id);
			curr->weight = r->weight - 1;
			return (1);
		}
		if (q->flow[curr->id][r->id] == 1)
			n = 1;
		link = link->next;
	}
	return (n);
}

static int	find_flow(t_queue *q, t_room *r, int prev_flow, t_lem_in *lem)
{
	t_list		*link;
	t_room		*curr;

	if (prev_flow == 0 && find_neg_flow(q, r, lem) == 1)
		return (0);
	link = r->link;
	while (link)
	{
		curr = link->content;
		if (curr->weight != MAX_INT)
			check_dist(lem, q, r, curr);
		if (q->visited[curr->id] != 1 && q->flow[r->id][curr->id] != 1
			&& (r->id != START_ID || curr->id != END_ID))
		{
			add_to_queue(q, curr->id, r->id);
			if (q->flow[r->id][curr->id] == 0)
				curr->weight = r->weight + 1;
			else
				curr->weight = r->weight - 1;
		}
		link = link->next;
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
	set_max_weights(lem); //if not visited change else is real
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
		{
			free_path(new);
			return ;
		}
		clear_queue(q);
	}
	t == 0 ? error_msg("No paths.\n") : 0;
}
