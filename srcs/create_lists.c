/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 06:32:19 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 06:50:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include "../error_msg.h"

t_room			*new_room(char *line, t_type type, t_lem_in *lem)
{
	char	**tmp;
	t_room	*room;

	tmp = ft_strsplit(line, ' ');
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL)
		error_msg(EXTRA_CRAP);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(tmp[0]);
	if (only_num(tmp[1]) == 0 || only_num(tmp[2]) == 0)
		error_msg(EXTRA_CRAP);
	room->yx[0] = ft_atoi(tmp[2]);
	room->yx[1] = ft_atoi(tmp[1]);
	room->yx[0] > lem->max ? lem->max = room->yx[0] : 0;
	room->yx[1] > lem->max ? lem->max = room->yx[1] : 0;
	room->type = type;
	room->paths[0] = 0;
	room->paths[1] = 0;
	room->ants_in = 0;
	room->bfs_val = -1;
	room->next = NULL;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	ft_strdel(&tmp[2]);
	free(tmp);
	return (room);
}

void				connect_room(t_lem_in *lem, t_room *room)
{
	t_room *current;

	if ((current = lem->rooms))
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->name, room->name) == 0 || (current->yx[0]
						== room->yx[0] && current->yx[1] == room->yx[1]))
				error_msg(SAME_CORDINATES);
			current = current->next;
		}
		ft_strcmp(current->name, room->name) == 0 ? error_msg(DUP_NAME) : 0;
		current->next = room;
	}
	else
		lem->rooms = room;
	if (room->type == START || room->type == END)
	{
		if (room->type == END && lem->end == NULL)
			lem->end = room;
		else if (room->type == START && lem->start == NULL)
			lem->start = room;
		else
			error_msg(DUPLICATE_SE);
	}
}

void				connect_link(t_lem_in *lem, t_link *link)
{
	t_link *current;

	current = lem->links;
	if (current)
	{
		while (current->next)
		{
			if ((current->start == link->start) && (current->end == link->end))
				error_msg(DUPLICATE_LINK);
			if ((current->start == link->end) && (current->end == link->start))
				error_msg(DUPLICATE_LINK);
			current = current->next;
		}
		current->next = link;
	}
	else
		lem->links = link;
}

t_link				*link_rooms(t_room *s, t_room *e)
{
	t_link *link;

	if (!(link = (t_link *)ft_memalloc(sizeof(t_link))))
		error_msg(MALLOC_ERROR);
	link->start = s;
	link->end = e;
	link->used = 0;
	link->next = NULL;
	link->prev = NULL;
	return (link);
}
