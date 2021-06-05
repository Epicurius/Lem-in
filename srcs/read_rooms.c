/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:20:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/05 17:08:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	start_end_rooms(t_lem_in *lem, t_room *room, int id)
{
	if (id == START_ID)
	{
		if (lem->start)
			error_msg("Duplicate Start rooms!");
		lem->start = room;
	}
	else if (id == END_ID)
	{
		if (lem->end)
			error_msg("Duplicate End rooms!");
		lem->end = room;
	}
}

t_room	*new_room(t_lem_in *lem, char *line, int id)
{
	char	**tmp;
	t_room	*room;

	tmp = ft_strsplit(line, ' ', NULL);
	if (tmp[0] && tmp[1] == NULL)
	{
		free(tmp);
		lem->room_nb -= 1;
		return (NULL);
	}
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL)
		error_msg(EXTRA_CRAP);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(tmp[0]);
	room->y = ft_atoi(tmp[2]);
	room->x = ft_atoi(tmp[1]);
	room->left = NULL;
	room->right = NULL;
	room->parent = NULL;
	room->flag = RB_RED;
	free(tmp);
	start_end_rooms(lem, room, id);
	room->id = id;
	return (room);
}

int	room_type(t_lem_in *lem, char *line)
{
	int	i;

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

t_room	*find_room(t_room *root, char *name)
{
	int		val;
	t_room	*node;

	node = root;
	while (1)
	{
		if (!node)
			return (NULL);
		val = ft_strcmp(node->name, name);
		if (val == 0)
			return (node);
		if (val > 0)
			node = node->left;
		else
			node = node->right;
	}
	return (NULL);
}
