/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 10:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/14 11:37:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
		if (q->flow[e][s] == 0)
		{
			q->flow[e][s] = -1;
			q->flow[s][e] = 1;
		}
		else if (q->flow[e][s] == -1 || q->flow[e][s] == 1)
		{
			q->flow[e][s] = 0;
			q->flow[s][e] = 0;
		}		e = s;
*/

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
		//printf("%d\n", link->content_size);
		//if (q->flow[e][s] == 0)
		if (link->content_size == 0)
		{
			link->content_size = -1;
			find_link(lem->id_table[s], e)->content_size = 1;
		}
		//else if (q->flow[e][s] == -1 || q->flow[e][s] == 1)
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

static int	find_neg_flow(t_queue *q, t_room *r, t_lem_in *lem)
{
	int		n = 0;
	t_list		*link;
	t_room		*curr;

	link = r->link;
	while (link)
	{
		curr = link->content;
		if (q->visited[curr->id] != 1 && link->content_size == -1)
		{
			if (q->visited[curr->id] != 0)
				check_dist(lem, q, r, curr);
			add_to_queue(q, curr->id, r->id);
			curr->weight = r->weight - 1;
			return (1);
		}
		if (find_link(curr, r->id)->content_size == 1)
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
		if (q->visited[curr->id] != 0)
			check_dist(lem, q, r, curr);
		if (q->visited[curr->id] != 1 && link->content_size != 1
				&& (r->id != START_ID || curr->id != END_ID))
		{
			add_to_queue(q, curr->id, r->id);
			if (link->content_size == 0)
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
	clear_queue(q);
	reset_queue(q, START_ID, END_ID);
	check_start_end(lem, q);
	while (++i < q->len && q->visited[END_ID] != 1 && q->queue[i] >= 0)
	{
		prev_flow = 0;
		room = q->queue[i];
		if (i > 0)
			prev_flow = find_link(lem->id_table[q->prev[room]], room)->content_size;
		find_flow(q, lem->id_table[room], prev_flow, lem);
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
