/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:20:15 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/12 17:24:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lem_in.h"
#include "./error_msg.h"

t_room 	*new_room(t_lem_in *lem, char *line, int id)
{
	char **tmp;
	t_room *room;

	tmp = ft_strsplit(line, ' ');
	if (tmp[0] && tmp[1] == NULL)
	{
		ft_strdel(&tmp[0]);
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
	room->links_nb = 0;
	room->weight = 0;
	room->flag = RB_RED;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	ft_strdel(&tmp[2]);
	free(tmp);
	if (id == START_ID)
		lem->start = room;
	else if (id == END_ID)
		lem->end = room;
	room->id = id;
	return (room);

}

int		room_type(t_lem_in *lem, char *line)
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

t_room	*find_room(t_room *root, char *name)
{
	int	val;
	t_room	*node;

	node = root;
	while (1)
	{
		if (!node)
			return (NULL);
		val = ft_strcmp(node->name, name);
		if (val == 0)
			return (node);
		node = val > 0 ? node->left : node->right;
	}
	return (NULL);
}
