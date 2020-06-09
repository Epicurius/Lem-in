/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 06:12:49 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 07:29:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		delet(t_lem_in *lem, t_link *link)
{
	t_link *pre;
	t_link *current;

	pre = NULL;
	current = lem->links;
	while (current && current != link)
	{
		pre = current;
		current = current->next;
	}
	if (!pre && current)
		lem->links = current->next;
	else if (current)
		pre->next = current->next;
	link->start->paths[1] -= (link->start->paths[1] > 0 ? 1 : 0);
	link->end->paths[0] -= (link->end->paths[0] > 0 ? 1 : 0);
	free(link);
}

void		un_link(t_link *link)
{
	link->start->paths[1] -= (link->start->paths[1] > 0 ? 1 : 0);
	link->end->paths[0] -= (link->end->paths[0] > 0 ? 1 : 0);
	link->used = -1;
}

void		trim_bfs(t_lem_in *lem)
{
	t_link *current;
	t_link *elem;

	current = lem->links;
	while (current)
	{
		elem = current;
		current = current->next;
		if (elem->start->bfs_val == -1 || elem->end->bfs_val == -1)
			delet(lem, elem);
		else if (elem->start->bfs_val == elem->end->bfs_val)
			un_link(elem);
	}
}

void		trim_forks(t_lem_in *lem)
{
	t_link *current;
	t_link *elem;

	current = lem->links;
	while (current)
	{
		elem = current;
		current = current->next;
		if (((elem->start->paths[0] == 0 && elem->start->bfs_val != 0)
			|| (elem->end != lem->end && elem->end->paths[1] == 0))
			&& elem->used != -1)
		{
			un_link(elem);
			trim_forks(lem);
			return ;
		}
	}
	return ;
}

void		keep_optimal(t_lem_in *lem, t_link *link, t_room *s, t_room *e)
{
	t_link *current;
	t_link *elem;

	current = lem->links;
	while (current)
	{
		elem = current;
		current = current->next;
		if (s != NULL && e == NULL)
			if (elem->start == s && elem != link && elem->used != -1)
				un_link(elem);
		if (e != NULL && s == NULL)
			if (elem->start == e && elem != link && elem->used != -1)
				un_link(elem);
	}
}
