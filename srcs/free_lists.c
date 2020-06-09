/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 09:34:43 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/08 09:34:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	free_rooms(t_lem_in *lem)
{
	t_room *current;
	t_room *elem;

	current = lem->rooms;
	while (current)
	{
		elem = current;
		current = current->next;
		free(elem->name);
		free(elem);
	}
}

void	free_links(t_link **current)
{
	t_link *elem;

	while ((*current))
	{
		elem = (*current);
		(*current) = (*current)->next;
		free(elem);
	}
}

void	free_routes(t_lem_in *lem)
{
	t_route *current;
	t_route *elem;

	current = lem->routes;
	while (current)
	{
		elem = current;
		current = current->next;
		free_links(&(elem->strt));
		free(elem);
	}
}

void	main_struct_free(t_lem_in *lem)
{
	free_rooms(lem);
	free_routes(lem);
	free_links(&lem->links);
}
