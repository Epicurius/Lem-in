
#include "lem_in.h"

void	reset_int_array(int **set, int length, int n)
{
	int i;

	i = 0;
	while (i < length)
	{
		set[0][i] = n;
		i += 1;
	}
}

void	reset_queue(t_queue *q, int s, int e)
{
	q->queue[0] = s;
	q->visited[s] = 1;
	q->position = 1;
	e >= 0 ? q->visited[e] = 0 : 0;
}

void	check_start_end(t_lem_in *lem, t_queue *q)
{
	int i;
	t_list *link;
	t_room *room;

	i = -1;
	link = lem->start->link;
	while (link)
	{
		room = link->content;
		if (room == lem->end)
		{
			link->content_size = 1;
			find_link(lem->end, START_ID)->content_size = -1;
			q->prev[END_ID] = START_ID;
			return ;
		}
		link = link->next;
	}
}

