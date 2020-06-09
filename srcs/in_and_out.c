/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_and_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 09:35:26 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 07:30:15 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	dead_ends(t_lem_in *lem)
{
	t_link *current;
	t_link *elem;

	current = lem->links;
	while (current)
	{
		elem = current;
		current = current->next;
		if ((elem->start->paths[0] == 0 && elem->start != lem->start
			&& elem->start->paths[1] > 0) || (elem->end->paths[0] > 0
			&& elem->end != lem->end && elem->end->paths[1] == 0))
		{
			if (elem->used != -1)
				un_link(elem);
		}
	}
}

void	in_and_out(t_lem_in *lem)
{
	t_link *current;

	current = lem->links;
	while (current)
	{
		if (current->used != -1)
		{
			current->start->paths[1] += 1;
			current->end->paths[0] += 1;
		}
		current = current->next;
	}
	dead_ends(lem);
}
