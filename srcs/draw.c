/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:27:39 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 07:06:29 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		square(int s_x, int s_y, int size, t_lem_in *lem)
{
	int		y;
	int		x;
	int		tmp;

	y = 0;
	tmp = 0;
	while (y < (size * 4))
	{
		x = 0;
		while (x < (size * 4))
		{
			lem->pic[x + tmp + ((s_y * WIDTH * 4) + (s_x * 4))] =
				lem->rgb;
			lem->pic[x + 1 + tmp + ((s_y * WIDTH * 4) + (s_x * 4))] =
				lem->rgb >> 8;
			lem->pic[x + 2 + tmp + ((s_y * WIDTH * 4) + (s_x * 4))] =
				lem->rgb >> 16;
			x += 4;
		}
		y += 4;
		tmp += (WIDTH * 4);
	}
}

t_room		*find_cords(t_lem_in *lem, int x, int y)
{
	t_room *current;

	current = lem->rooms;
	while (current)
	{
		if (current->yx[1] == y && current->yx[0] == x)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void		draw_values(t_lem_in *lem, t_room *current, int x, int y)
{
	int		size;
	char	*ants;

	ants = ft_itoa(current->ants_in);
	size = (WIDTH / lem->max) - ((WIDTH / lem->max) / 2);
	mlx_string_put(lem->mlx, lem->win, (x * size) * 2, (y * size) * 2,
		0xFFFFFF, current->name);
	if (current->ants_in != 0)
		mlx_string_put(lem->mlx, lem->win, (x * size) * 2 + (size / 3),
			(y * size) * 2 + (size / 3), 0xFFFFFF, ants);
	ft_strdel(&ants);
	free(ants);
}

void		draw_map(t_lem_in *lem, int i)
{
	int			y;
	int			x;
	int			size;
	t_room		*current;

	if (lem->enable_visuals != 1)
		return ;
	size = (WIDTH / lem->max) - ((WIDTH / lem->max) / 2);
	y = -1;
	while (++y < lem->max)
	{
		x = -1;
		while (++x < lem->max)
		{
			lem->rgb = 0x66ffff;
			current = find_cords(lem, y, x);
			if (current != NULL)
			{
				if (current->type == START || current->type == END)
					lem->rgb = current->type == START ? 0xffff00 : 0x66ff66;
				draw_values(lem, current, x, y);
				i == 0 ? square((x * size) * 2, (y * size) * 2, size, lem) : 0;
			}
		}
	}
}

void		draw_links(t_lem_in *lem, int x)
{
	t_link	*current;
	int		start[2];
	int		end[2];
	int		size;

	if (lem->enable_visuals != 1)
		return ;
	size = (WIDTH / lem->max) - ((WIDTH / lem->max) / 2);
	current = lem->links;
	while (current)
	{
		if (current->used == -1 || x == 1)
			lem->rgb = 0xFF0000;
		else
			lem->rgb = 0x00FF00;
		start[1] = (current->start->yx[1] * size) * 2;
		start[0] = (current->start->yx[0] * size) * 2;
		end[1] = (current->end->yx[1] * size) * 2;
		end[0] = (current->end->yx[0] * size) * 2;
		line(lem, start, end);
		current = current->next;
	}
}
