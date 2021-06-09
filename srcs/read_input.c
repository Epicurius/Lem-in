/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 11:06:49 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/09 16:49:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	print_input(char **line, unsigned char i)
{
	if (i == 0 || i == 2)
	{
		ft_putstr(*line);
		write(1, "\n", 1);
	}
	ft_strdel(line);
}

void	read_links(char *line, t_lem_in *lem)
{
	while (get_next_line(0, &line))
	{
		if (line[0] != '#')
			find_links(line, lem);
		print_input(&line, lem->flag.format);
	}
}

char	*read_rooms(char *line, t_lem_in *lem)
{
	int		id;
	t_room	*room;

	while (get_next_line(0, &line))
	{
		id = room_type(lem, line);
		if (id == START_ID || id == END_ID)
		{
			print_input(&line, lem->flag.format);
			get_next_line(0, &line);
			room = new_room(lem, line, id);
			rb_insert((&lem->tree), room);
		}
		else if (id != -1)
		{
			room = new_room(lem, line, id);
			if (!room)
				return (line);
			rb_insert((&lem->tree), room);
		}
		if (lem->min_moves == NULL && ft_strstr(line, LINES_REQUIRED))
			lem->min_moves = ft_strdup(line);
		print_input(&line, lem->flag.format);
	}
	return (NULL);
}

void	read_ants(t_lem_in *lem, char *line)
{
	while (get_next_line(0, &line))
	{
		if (!(line[0] == '#' && line[1] != '#'))
		{
			lem->ants = ft_atoi(line);
			print_input(&line, lem->flag.format);
			if (lem->ants > 2147483647 || lem->ants < 0)
				error_msg(WRONG_ANT_AMOUNT);
			return ;
		}
		print_input(&line, lem->flag.format);
	}
}

void	read_input(t_lem_in *lem)
{
	char	*line;

	line = NULL;
	lem->min_moves = NULL;
	read_ants(lem, line);
	line = read_rooms(line, lem);
	if (line == NULL)
		error_msg("No links.");
	if (lem->end == NULL || lem->start == NULL)
		error_msg(MISSING_ROOM);
	lem->id_table = ft_memalloc(sizeof(t_room *) * (lem->room_nb + 1));
	if (!lem->id_table)
		error_msg("id_table malloc\n");
	find_links(line, lem);
	if (lem->links_nb <= 0)
		error_msg("No links.");
	print_input(&line, lem->flag.format);
	read_links(line, lem);
	free(line);
}
