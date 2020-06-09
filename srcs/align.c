/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 09:26:34 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/08 09:26:47 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		swap(t_room **start, t_room **end)
{
	t_room *tmp;

	tmp = *start;
	*start = *end;
	*end = tmp;
}

void		align(t_lem_in *lem)
{
	t_link *current;

	current = lem->links;
	while (current)
	{
		if ((current->start->bfs_val > current->end->bfs_val)
				&& current->used != -1)
			swap(&current->start, &current->end);
		current = current->next;
	}
}
