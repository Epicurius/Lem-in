/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 10:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/16 15:58:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*find_link(t_room *r, int e)
{
	t_list *curr;

	curr = r->link;
	while (curr)
	{
		if (get_room(curr)->id == e)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static void	save_flow(t_queue *q, t_lem_in *lem)
{
	int		e;
	int		s;
	t_list *link;

	e = END_ID;
	if (q->prev[e] == START_ID)
		return ;
	while (e != START_ID)
	{
		s = q->prev[e];
		link = find_link(lem->id_table[e], s);
		if (link->content_size == 0)
		{
			link->content_size = -1;
			find_link(lem->id_table[s], e)->content_size = 1;
		}
		else if (link->content_size == -1 || link->content_size == 1)
		{
			link->content_size = 0;
			find_link(lem->id_table[s], e)->content_size = 0;
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

t_room *follow_neg_flow(t_queue *q, t_room *r, t_lem_in *lem)
{
	t_list	*link;
	t_room	*curr;

	link = r->link;
	if (r->id == START_ID)
		return (NULL);
	while (link)
	{
		curr = link->content;
		if (q->visited[curr->id] != 1 && link->content_size == 0)
			return (r);
		link = link->next;
	}
	return (find_neg_flow(q, r, lem));

}

t_room *find_neg_flow(t_queue *q, t_room *r, t_lem_in *lem)
{
	t_list	*link;
	t_room	*curr;

	link = r->link;
	while (link)
	{
		curr = link->content;
		if (q->visited[curr->id] != 1 && link->content_size == -1)
		{
			q->prev[curr->id] = r->id;
			q->visited[curr->id] = 1;
			return (follow_neg_flow(q, curr, lem));
		}
		link = link->next;
	}
	return (r);
}

static int	find_flow(t_queue *q, t_room *r, int prev_flow, t_lem_in *lem)
{
	t_list		*link;
	t_room		*curr;

	if ((r = find_neg_flow(q, r, lem)) == NULL)
		return (1);
	link = r->link;
	while (link)
	{
		curr = link->content;
		if (q->visited[curr->id] != 1 && link->content_size != 1)
			add_to_queue(q, curr->id, r->id);
		link = link->next;
	}
	return (0);
}
static int	optimise_flow(t_lem_in *lem, t_queue *q, int *t)
{
	int		i;
	int prev_flow =0;
	int		room;

	i = -1;
	clear_queue(q);
	reset_queue(q, START_ID, END_ID);
	check_start_end(lem, q);
	//while (++i < q->len && i < q->position) //slow
	while (++i < q->len && q->visited[END_ID] != 1 && q->queue[i] >= 0)
	{
		room = q->queue[i];
		find_flow(q, lem->id_table[room], prev_flow, lem);
		if (lem->flag.queue == 1)
			print_queue(lem, q, i);
	}
	if (q->prev[END_ID] == -1 || (q->prev[END_ID] == START_ID && *t == 1))
		return (0);
	return (*t = 1);
}

void	free_paths(t_path *paths, int len)
{
	int i;

	i = -1;
	while (++i < len)
		ft_memdel((void*)&paths[i]);
	free(paths);
}

void	path_find(t_lem_in *lem, t_queue *q)
{
	int		i;
	int		t;
	int		moves;
	int		path_nb;
	t_path *tmp;

	t = 0;
	lem->start->weight = 0;
	while (optimise_flow(lem, q, &t))
	{
		save_flow(q, lem);
		if (!(tmp = ft_memalloc(sizeof(t_path) * (lem->max_paths))))
			error_msg("Malloc: lem->path_l.paths.");
		moves = save_paths(q, lem, tmp);
		if (lem->path_l.moves == 0 || lem->path_l.moves >= moves)
		{
			free_paths(lem->path_l.paths, lem->max_paths);
			if (!(lem->path_l.paths = ft_memalloc(sizeof(t_path) * (lem->max_paths))))
				error_msg("Malloc: lem->path_l.paths.");
			i = -1;
			while (++i < lem->max_paths)
				memcpy(&lem->path_l.paths[i], &tmp[i], sizeof(tmp[i]));
			lem->path_l.moves = moves;
			free(tmp);
		}
		else
		{
			if (lem->flag.full == 0)
				return (free_paths(tmp, lem->max_paths));
			free_paths(tmp, lem->max_paths);
		}
		clear_queue(q);
	}
	t == 0 ? error_msg("No paths.\n") : 0;
}
