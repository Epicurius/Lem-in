/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:05:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/12 14:04:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_list	*find_link(t_room *r, int e)
{
	t_list	*curr;

	curr = r->link;
	while (curr)
	{
		//if (get_room(curr)->id == e)
		if (((t_room *)curr->content)->id == e)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	save_flow(t_queue *q, t_env *lem)
{
	int		e;
	int		s;
	t_list	*link;

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

void	free_paths(t_path *paths, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		ft_memdel((void *)&paths[i]);
	free(paths);
}
