/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_routes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 09:31:35 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/08 09:32:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include "../error_msg.h"

t_route		*create_a_route(void)
{
	t_route	*route;

	if (!(route = (t_route *)ft_memalloc(sizeof(t_route))))
		error_msg(MALLOC_ERROR);
	route->strt = NULL;
	route->len = 0;
	route->is_ant = 0;
	route->next = NULL;
	return (route);
}

t_link		*disconnect_link(t_lem_in *lem, t_link *link)
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
	link->next = NULL;
	return (link);
}

void		connect_route(t_route *route, t_link *link)
{
	t_link	*pre;
	t_link	*current;

	pre = NULL;
	current = route->strt;
	if (current)
	{
		while (current)
		{
			pre = current;
			current = current->next;
		}
		link->prev = pre;
		pre->next = link;
	}
	else
		route->strt = link;
	route->len += 1;
}

void		add_route(t_lem_in *lem, t_route *route)
{
	t_route	*pre;
	t_route	*current;

	pre = NULL;
	current = lem->routes;
	if (current)
	{
		while (current && route->len > current->len)
		{
			pre = current;
			current = current->next;
		}
		if (!pre)
			lem->routes = route;
		else
			pre->next = route;
		route->next = current;
	}
	else
		lem->routes = route;
}

void		create_routes(t_lem_in *lem)
{
	t_route	*route;
	t_link	*link;

	clean(lem);
	while (1)
	{
		route = create_a_route();
		if ((link = find_link(lem, lem->start, NULL)) == NULL)
		{
			free(route);
			return ;
		}
		link = disconnect_link(lem, link);
		connect_route(route, link);
		while (link->end != lem->end)
		{
			if ((link = find_link(lem, link->end, NULL)) == NULL)
				break ;
			link = disconnect_link(lem, link);
			connect_route(route, link);
		}
		add_route(lem, route);
	}
}
