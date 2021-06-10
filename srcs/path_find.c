/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 10:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 17:04:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int	find_flow(t_queue *q, t_room *r, int prev_flow, t_lem_in *lem)
{
	t_list		*link;
	t_room		*curr;

	r = find_neg_flow(q, r, lem);
	if (!r)
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
	int		prev_flow;
	int		room;

	i = -1;
	prev_flow = 0;
	clear_queue(q);
	reset_queue(q, START_ID, END_ID);
	check_start_end(lem, q);
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

void	path_find2(t_lem_in *lem, t_path *tmp, int moves)
{
	int	i;

	if (lem->path_l.moves == 0 || lem->path_l.moves >= moves)
	{
		free_paths(lem->path_l.paths, lem->max_paths);
		lem->path_l.paths = ft_memalloc(sizeof(t_path) * lem->max_paths);
		if (!lem->path_l.paths)
			error_msg("Malloc: lem->path_l.paths.");
		i = -1;
		while (++i < lem->max_paths)
			ft_memcpy(&lem->path_l.paths[i], &tmp[i], sizeof(tmp[i]));
		lem->path_l.moves = moves;
		free(tmp);
	}
	else
		return (free_paths(tmp, lem->max_paths));
}

void	path_find(t_lem_in *lem, t_queue *q)
{
	int		t;
	int		path_nb;
	t_path	*tmp;

	t = 0;
	lem->start->weight = 0;
	while (optimise_flow(lem, q, &t))
	{
		save_flow(q, lem);
		tmp = ft_memalloc(sizeof(t_path) * lem->max_paths);
		if (!tmp)
			error_msg("Malloc: lem->path_l.paths.");
		path_find2(lem, tmp, save_paths(q, lem, tmp));
		clear_queue(q);
	}
	if (t == 0)
		error_msg("No paths.");
}
