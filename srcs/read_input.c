/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:40:37 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 07:28:07 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include "../error_msg.h"

static t_type		room_type(char *line)
{
	if (line[0] == 'L')
		error_msg(L_START);
	if (ft_strcmp(line, "##start") == 0)
		return (START);
	else if (ft_strcmp(line, "##end") == 0)
		return (END);
	else if (line[0] == '#')
		return (COMMENT);
	else
		return (MIDDLE);
}

t_room				*find_room(t_lem_in *lem, char *name)
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

int					read_links(char *line, t_lem_in *lem, int len, int dash)
{
	char	*strt;
	char	*end;
	t_room	*start_room;
	t_room	*end_room;

	if (ft_strstr(line, "-") == 0 || dash == (len - 1))
		error_msg(NOT_VALID_LINK);
	strt = ft_strsub(line, 0, dash);
	end = ft_strsub(line, ft_strlen(strt) + 1, len);
	start_room = find_room(lem, strt);
	end_room = find_room(lem, end);
	free(strt);
	free(end);
	if (start_room && end_room)
	{
		if (ft_strcmp(start_room->name, end_room->name) == 0)
			error_msg(BAD_LINK);
		connect_link(lem, link_rooms(start_room, end_room));
	}
	else
		read_links(line, lem, len, dash + 1);
	return (0);
}

void				read_rooms(char *line, t_lem_in *lem)
{
	t_room		*room;
	t_type		type;

	while (get_next_line(0, &line) > 0)
	{
		input_copy(lem, line);
		if ((type = room_type(line)) != COMMENT)
		{
			if ((ft_strchr(line, ' ') == NULL) && type == MIDDLE)
			{
				if (lem->end == NULL || lem->start == NULL)
					error_msg(MISSING_ROOM);
				read_links(line, lem, ft_strlen(line), 1);
			}
			else
			{
				type != MIDDLE ? ft_strdel(&line) : 0;
				type != MIDDLE ? input_copy(lem, line) : 0;
				type != MIDDLE ? get_next_line(0, &line) : 0;
				connect_room(lem, (room = new_room(line, type, lem)));
			}
		}
		ft_strdel(&line);
	}
}

int					read_input(t_lem_in *lem)
{
	char *line;

	line = NULL;
	lem->org_input = NULL;
	while (get_next_line(0, &line) > 0)
	{
		input_copy(lem, line);
		if (!(line[0] == '#' && line[1] != '#'))
		{
			if (only_num(line) == 0)
				error_msg(ANT_ERROR);
			lem->ants = ft_atoi(line);
			break ;
		}
		ft_strdel(&line);
	}
	if (lem->ants > 2147483647 || lem->ants <= 0)
		error_msg(WRONG_ANT_AMOUNT);
	ft_strdel(&line);
	read_rooms(line, lem);
	if (lem->links == NULL)
		error_msg(NO_LINKS);
	lem->max += 1;
	free(line);
	return (0);
}
