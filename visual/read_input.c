/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 09:35:30 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/04 08:56:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vis.h"
#include <stdio.h>

static t_type	room_type(char *line)
{
	if (ft_strcmp(line, "##start") == 0)
		return (START);
	else if (ft_strcmp(line, "##end") == 0)
		return (END);
	else if (line[0] == '#' && line[1] != '#')
		return (COMMENT);
	else
		return (MIDDLE);
}

static t_room 		*new_room(char *line, t_type type, t_lem_in *lem)
{
	char **tmp;
	t_room *room;
	
	tmp = ft_strsplit(line, ' ');
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(tmp[0]);
	room->yx[0] = ft_atoi(tmp[2]);
	room->yx[1] = ft_atoi(tmp[1]);
	room->yx[0] > lem->max[0] ? lem->max[0] = room->yx[0] : 0;
	room->yx[1] > lem->max[1] ? lem->max[1] = room->yx[1] : 0;
	room->type = type;
	room->paths[0] = 0;
	room->paths[1] = 0;
	room->ants_in = 0;
	room->next = NULL;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	ft_strdel(&tmp[2]);
	free(tmp);
	return (room);
}

void	connect_room(t_lem_in *lem, t_room *room)
{
	t_room *current;

	if ((current = lem->rooms))
	{
		while (current->next != NULL)
			current = current->next;
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
	}
}

t_room		*find_room(t_lem_in *lem, char *name)
{
	t_room *current;
	
	current = lem->rooms;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	connect_link(t_lem_in *lem, t_link *link)
{
	t_link *current;

	current = lem->links;
	if (current)
	{
		while (current->next)
		{
			//if ((current->start == link->start) && (current->end == link->end))
			//	error_msg(DUPLICATE_LINK);
			//if ((current->start == link->end) && (current->end == link->start))
			//	error_msg(DUPLICATE_LINK);
			current = current->next;
		}
		current->next = link;
	}
	else
		lem->links = link;
}

t_link	*link_rooms(t_room *s, t_room *e)
{
	t_link *link;

	link = (t_link *)ft_memalloc(sizeof(t_link));
	link->start = s;
	link->end = e;
	link->used = 0;
	link->next = NULL;
	link->prev = NULL;
	return (link);	
}

int	read_links(char *line, t_lem_in *lem, int len, int dash)
{
	char *strt;
	char *end;
	t_room *room;
	t_room *start_room;
	t_room *end_room;
	
	strt = ft_strsub(line, 0, dash);
	end = ft_strsub(line, ft_strlen(strt) + 1, len);
	start_room = find_room(lem, strt);
	end_room = find_room(lem, end);
	free(strt);
	free(end);
	if (start_room && end_room)
		connect_link(lem, link_rooms(start_room, end_room));
	else
		read_links(line, lem, len, dash + 1);
	return (0);
}

int	read_rooms(char *line, t_lem_in *lem)
{
	t_room *room;
	t_type type;
	int len;

	while (get_next_line(0, &line) > 0)
	{
		if ((type = room_type(line)) != COMMENT)
		{
			if ((ft_strchr(line, ' ') == NULL) && type == MIDDLE)
			{
				len = ft_strlen(line);
				read_links(line, lem, len, 1);
			}
			else
			{
				if (type != MIDDLE)
				{
					ft_strdel(&line); //maybe move to room_type
					get_next_line(0, &line);
				}
				connect_room(lem, (room = new_room(line, type, lem)));
			}
		}
		ft_strdel(&line);
	}
	return (0);
}

int	read_input(t_lem_in *lem)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!(line[0] == '#' && line[1] != '#'))
		{
			lem->ants = ft_atoi(line);
			break ;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	read_rooms(line, lem);
	lem->max[0] += 1;
	lem->max[1] += 1;
	free(line);
	return (0);
}
