/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 11:06:49 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/09 14:59:31 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../validator.h"

void	read_links(char *line, t_env *lem)
{
	find_links(line, lem);
	while (get_next_line(0, &line))
	{
		if (ft_strequ(line, ""))
		{
			free(line);
			return ;
		}
		if (line[0] != '#')
			find_links(line, lem);
		free(line);
	}
}

char	*read_rooms(char *line, t_env *lem)
{
	int		id;
	t_room	*room;

	while (get_next_line(0, &line))
	{
		id = room_type(lem, line);
		if (id == START_ID || id == END_ID)
		{
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
	}
	return (NULL);
}

void	read_ants(t_env *lem, char *line)
{
	int ants;

	while (get_next_line(0, &line))
	{
		if (!(line[0] == '#' && line[1] != '#'))
		{
			ants = ft_atoi(line);
			if (ants > 2147483647 || ants < 0)
				error_msg(WRONG_ANT_AMOUNT);
			lem->ants = ft_memalloc(sizeof(t_room *) * (ants + 1));
			lem->ant_nb = ants;
			return ;
		}
	}
}

void	read_input(t_env *lem)
{
	char	*line;

	line = NULL;
	read_ants(lem, line);
	line = read_rooms(line, lem);
	if (line == NULL)
		error_msg("No links.");
	if (lem->end == NULL || lem->start == NULL)
		error_msg(MISSING_ROOM);
	read_links(line, lem);
	free(line);
}
