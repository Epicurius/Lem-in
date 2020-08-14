/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:12:02 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/14 10:58:17 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lem_in.h"
#include "./error_msg.h"

void	create_link(t_lem_in *lem, t_room *left, t_room *right)
{
	t_list	*node;

	if (!(node = ft_lstnew(0, 0)))
		error_msg("Malloc node.");
	node->content = right;
	if (!(left->link))
	{
		left->link = node;
		left->flag = 0;
	}
	else
		ft_lstadd(&(left->link), node);
	if (!(node = ft_lstnew(0, 0)))
		error_msg("Malloc node.");
	node->content = left;
	if (!(right->link))
	{
		right->link = node;
		right->flag = 0;
	}
	else
		ft_lstadd(&(right->link), node);
	left->links_nb += 1;
	right->links_nb += 1;
}

void	find_links(char *line, t_lem_in *lem)
{
	char *strt;
	char *end;
	int len;
	t_room *start_room;
	t_room *end_room;

	len = 0;
	while (line[len] != '-' && line[len] != '\0')
		len++;
	strt = ft_strndup(line, len);
	line = ft_strchr(line, '-') + 1;
	len = 0;
	while (line[len] != '\0')
		len++;
	end = ft_strndup(line, len);
	start_room = find_room(lem->tree, strt);
	end_room = find_room(lem->tree, end);
	free(strt);
	free(end);
	if (start_room && end_room)
	{
		create_link(lem, start_room, end_room);
		if (lem->id_table[start_room->id] == NULL)
			lem->id_table[start_room->id] = start_room;
		if (lem->id_table[end_room->id] == NULL)
			lem->id_table[end_room->id] = end_room;
		lem->links_nb += 1;
	}
	else
		error_msg("No room found with that name.");
}
