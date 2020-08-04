
#include "./lem_in.h"
#include "./error_msg.h"
#include <stdio.h>

static void	print_input(char **line)
{
	//ft_putstr(*line);
	//write(1, "\n", 1);
	ft_strdel(line);
}

t_room 		*new_room(t_lem_in *lem, char *line, int id)
{
	char **tmp;
	t_room *room;
	
	tmp = ft_strsplit(line, ' ');
	if (tmp[0] && tmp[1] == NULL)
	{
		lem->room_nb -= 1;
		return (NULL);
	}
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL)
		error_msg(EXTRA_CRAP);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(tmp[0]);
	if (only_num(tmp[1]) == 0 || only_num(tmp[2]) == 0)
		error_msg(EXTRA_CRAP);
	room->yx[0] = ft_atoi(tmp[2]);
	room->yx[1] = ft_atoi(tmp[1]);
	room->id = id;
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

t_room		*find_room(t_lem_in *lem, char *name) //this take 50% of time
{
	int i;

	i = -1;
	while (++i < lem->room_nb)
	{
		if (name[0] == lem->id_table[i]->name[0])
			if (ft_strcmp(lem->id_table[i]->name, name) == 0)
				return (lem->id_table[i]);
	}
	return (NULL);
}

void	find_links(char *line, t_lem_in *lem)
{
	char	*strt;
	char	*end;
	int		len;
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
	start_room = find_room(lem, strt); //return id
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
}

static t_type	room_type(t_lem_in *lem, char *line)
{
	int i;

	if (line[0] == '#')
	{
		if (!ft_strcmp(line, "##start"))
			return (START_ID);
		else if (!ft_strcmp(line, "##end"))
			return (END_ID);
		else
			return (-1);
	}
	if (line[0] == 'L')
		error_msg(L_START);
	return (lem->room_nb++);
}

char	*read_rooms(char *line, t_lem_in *lem)
{
	t_room *room;
	int id;

	while (get_next_line(0, &line))
	{
		id = room_type(lem, line);
		if (id == START_ID || id == END_ID)
		{
			print_input(&line);
			get_next_line(0, &line);	
			connect_room(lem, new_room(lem, line, id));
		}
		else if (id != -1)
		{
			if ((room = new_room(lem, line, id)) == NULL)
				return (line);
			connect_room(lem, room);
		}
		if (lem->min_moves == NULL && ft_strstr(line, LINES_REQUIRED))
			lem->min_moves = ft_strdup(line);
		print_input(&line);
	}
	return (NULL);
}

void	read_links(char *line, t_lem_in *lem)
{
	t_type type;
	int i;

	i = 0;
	lem->links = ft_memalloc(sizeof(int*) * (lem->room_nb + 1));
	while (i < lem->room_nb + 1)
		lem->links[i++] = ft_memalloc(sizeof(int) * (lem->room_nb + 1));
	find_links(line, lem);
	while (get_next_line(0, &line))
	{
		if (line[0] != '#')
			find_links(line, lem);
		print_input(&line);
	}
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

void	read_ants(t_lem_in *lem, char *line)
{
	while (get_next_line(0, &line))
	{
		if (!(line[0] == '#' && line[1] != '#'))
		{
			if (only_num(line) == 0)
				error_msg(ANT_ERROR);
			lem->ants = ft_atoi(line);
			print_input(&line);
			if (lem->ants > 2147483647 || lem->ants <= 0)
				error_msg(WRONG_ANT_AMOUNT);
			return ;
		}
		print_input(&line);
	}
}

void	read_input(t_lem_in *lem)
{
	char *line;

	line = NULL;
	read_ants(lem, line);
	line = read_rooms(line, lem);
	if (lem->end == NULL || lem->start == NULL)
		error_msg(MISSING_ROOM);
	create_table(lem, lem->rooms);
	read_links(line, lem);
	free(line);
}
