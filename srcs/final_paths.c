/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 09:33:55 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/08 09:34:19 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		is_end(t_lem_in *lem, t_link *link)
{
	if (link == NULL)
		return (0);
	if (link->end == lem->end)
		return (1);
	return (is_end(lem, find_link(lem, link->end, NULL)));
}

int		how_many_paths(t_lem_in *lem)
{
	int		used_paths;
	t_link	*current;

	used_paths = 0;
	current = lem->links;
	while (current)
	{
		if (current->start == lem->start && current->used != -1)
			used_paths += 1;
		current = current->next;
	}
	if (used_paths < lem->max_rout)
	{
		if (last_chance(lem, lem->start) == 1)
			used_paths += 1;
		return (used_paths);
	}
	else
		return (used_paths);
}
