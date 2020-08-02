
#include "./lem_in.h"
#include "./error_msg.h"
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

t_room 		*new_room(t_lem_in *lem, char *line, t_type type)
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
	if (type == START || type == END)
		room->id = type == START ? 0 : 1;
	else
		room->id = lem->room_nb++; 
	room->next = NULL;
	room->prev = NULL;
	room->links_nb = 0;
	room->ant_id = 0;
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
		room->prev = current;
	}
	else
		lem->rooms = room;
	if (room->id == START_ID || room->id == END_ID)
	{
		if (room->id == END_ID && lem->end == NULL)
			lem->end = room;
		else if (room->id == START_ID && lem->start == NULL)
			lem->start = room;
		else
			error_msg("Dupicate Start or Ends.");
	}
}

t_room	*find_room(t_lem_in *lem, char *name)
{
	int i;
	
	i = -1;
	while (++i < lem->room_nb)
	{
		if (ft_strcmp(lem->id_table[i]->name, name) == 0)
			return (lem->id_table[i]);
	}
	return (NULL);
}

int	find_links(char *line, t_lem_in *lem)
{
	char	*strt;
	char	*end;
	int		len;
	t_room	*start_room;
	t_room	*end_room;
	
	len = 0;
	while (line[len] != '-' && line[len] != '\0')
		len++;
	strt = ft_strndup(line, len);
	line = ft_strchr(line, '-') + 1;
	len = 0;
	while (line[len] != '\0')
		len++;
	end = ft_strndup(line, len);
	start_room = find_room(lem, strt);
	end_room = find_room(lem, end);
	free(strt);
	free(end);
	if (start_room && end_room)
	{
		lem->links[start_room->id][end_room->id] = 1;
		lem->links[end_room->id][start_room->id] = 1;
		start_room->links_nb += 1;
		end_room->links_nb += 1;
	}
	return (0);
}

char	*read_rooms(char *line, t_lem_in *lem)
{
	t_room *room;
	t_type type;

	while (get_next_line(0, &line) > 0)
	{
		//printf("%s\n", line); ///////////////////////////////////////
		if ((type = room_type(line)) != COMMENT)
		{
			if ((ft_strchr(line, ' ') == NULL) && type == MIDDLE)
			{
				if (lem->end == NULL || lem->start == NULL)
					error_msg(MISSING_ROOM);
				return (line);
			}
			else
			{
				type != MIDDLE ? ft_strdel(&line) : 0;
				type != MIDDLE ? get_next_line(0, &line) : 0;
				connect_room(lem, new_room(lem, line, type));
			}
		}
		if (ft_strstr(line, "#Here is the number of lines required:") != NULL && lem->min_moves == NULL)
			lem->min_moves = ft_strdup(line);
		ft_strdel(&line);
	}
	return (NULL);
}

int	read_links(char *line, t_lem_in *lem)
{
	t_type type;
	int i;

	i = 0;
	lem->links = ft_memalloc(sizeof(int*) * (lem->room_nb + 1));
	while (i < lem->room_nb + 1)
		lem->links[i++] = ft_memalloc(sizeof(int) * (lem->room_nb + 1));
	find_links(line, lem);
	while (get_next_line(0, &line) > 0)
	{
		//printf("%s\n", line); ///////////////////////////////////////
		if ((type = room_type(line)) != COMMENT)
			find_links(line, lem);
		ft_strdel(&line);
	}
	return (0);
}

void	create_table(t_lem_in *lem, t_room *room)
{
	if (!(lem->id_table = ft_memalloc(sizeof(t_room *) * (lem->room_nb + 1))))
		error_msg("Id_table malloc\n");
	while (room->next)
	{
		lem->id_table[room->id] = room;
		room = room->next;
	}
	lem->id_table[room->id] = room;
}


void	read_input(t_lem_in *lem)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		//printf("%s\n", line); ///////////////////////////////////////
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
	line = read_rooms(line, lem);
	create_table(lem, lem->rooms);
	read_links(line, lem);
	//printf("\n");
	free(line);
}
