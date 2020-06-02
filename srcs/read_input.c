
#include "../lem_in.h"
#include "../error_msg.h"
#include <stdio.h>

static t_type	room_type(char *line)
{
	if (line[0] == 'L')
		error_msg(L_START);
	if (ft_strcmp(line, "##start") == 0)
		return (START);
	else if (ft_strcmp(line, "##end") == 0)
		return (END);
	else if (line[0] == '#' && line[1] != '#')
		return (COMMENT);
	else
		return (MIDDLE);
}

static t_room 		*new_room(char *line, t_type type)
{
	char **tmp;
	t_room *room;
	
	tmp = ft_strsplit(line, ' ');
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL)
		error_msg(EXTRA_CRAP);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(tmp[0]);
	if (only_num(tmp[1]) == 0 || only_num(tmp[2]) == 0)
		error_msg(EXTRA_CRAP);
	room->yx[0] = ft_atoi(tmp[2]);
	room->yx[1] = ft_atoi(tmp[1]);
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

void	connect_room(t_lem_in *lem, t_room *room)
{
	t_room *current;

	if ((current = lem->rooms))
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->name, room->name) == 0)
				error_msg(SAME_ROOM_NAME);
			if (current->yx[0] == room->yx[0] && current->yx[1] == room->yx[1])
				error_msg(SAME_CORDINATES);
			current = current->next;
		}
		if (ft_strcmp(current->name, room->name) == 0)
			error_msg(SAME_ROOM_NAME);
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

t_link	*link_rooms(t_room *s, t_room *e)
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

int	read_links(char *line, t_lem_in *lem, int len, int dash)
{
	char *strt;
	char *end;
	t_room *room;
	t_room *start_room;
	t_room *end_room;
	
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

int	read_rooms(char *line, t_lem_in *lem)
{
	t_room *room;
	t_type type;
	int len;

	while (get_next_line(0, &line) > 0)
	{
		input_copy(lem, line);
		if ((type = room_type(line)) != COMMENT)
		{
			if ((ft_strchr(line, ' ') == NULL) && type == MIDDLE)
			{
				if (lem->end == NULL || lem->start == NULL)
					error_msg(MISSING_ROOM);
				len = ft_strlen(line);
				read_links(line, lem, len, 1);
			}
			else
			{
				if (type != MIDDLE)
				{
					ft_strdel(&line); //maybe move to room_type
					get_next_line(0, &line);
					input_copy(lem, line);
				}
				connect_room(lem, (room = new_room(line, type)));
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
	free(line);
	return (0);
}

int main(void)
{
	t_lem_in *lem;
	
	lem = (t_lem_in *)malloc(sizeof(* lem));
	lem->end = NULL;
	lem->start = NULL;
	read_input(lem);
	print_map(lem);
	bfs_value(lem);
	trim_bfs(lem);
	align(lem);
	in_and_out(lem);
	lem->max_rout = (lem->start->paths[1] > lem->end->paths[0] 
		? lem->end->paths[0] : lem->start->paths[1]);
	trim_input(lem);
	trim_output(lem);
	trim_forks(lem);
	lem->max_rout = how_many_paths(lem);
	if (lem->max_rout == 0)
		error_msg(NO_PATHS);
	create_routes(lem);
	ant_algo(lem);
	main_struct_free(lem);
	return (0);
}
