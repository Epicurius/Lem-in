/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:20:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/09 13:04:43 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../validator.h"

static void	start_end_rooms(t_env *lem, t_room *room, int id)
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

t_room	*new_room(t_env *lem, char *line, int id)
{
	int		nb;
	char	**tmp;
	t_room	*room;

	if (line[0] == '#')
		error_msg("Comment after star or end: %s", line);
	tmp = ft_strsplit(line, ' ', &nb);
	if (nb != 3)
	{
		free(tmp);
		if (nb == 1 && ft_strstr(line, "-") && line[0] != '#')
			return (NULL);
		error_msg(EXTRA_CRAP);
	}
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(tmp[0]);
	room->y = ft_atoi(tmp[2]);
	room->x = ft_atoi(tmp[1]);
	room->link = NULL;
	room->flag = RB_RED;
	free(tmp);
	if (find_room(lem->tree, room->name))
		error_msg("%s <- Duplicate rooms.", line);
	start_end_rooms(lem, room, id);
	room->id = id;
	return (room);
}

int	room_type(t_env *lem, char *line)
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
