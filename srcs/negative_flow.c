/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_flow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:13:22 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/12 13:55:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*follow_neg_flow(t_queue *q, t_room *r, t_env *lem)
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

t_room	*find_neg_flow(t_queue *q, t_room *r, t_env *lem)
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
