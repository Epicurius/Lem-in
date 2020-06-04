/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:27:39 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/04 11:36:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vis.h"
#include "../libft/libft.h"
#include "../libft/get_next_line.h"

void		background(t_lem_in *lem)
{
	int	x;
	int	color;

	color = 0x363636;
	x = 0;
	while (x < (HEIGHT * WIDTH * 4))
	{
		lem->pic[x] = color;
		x++;
	}
}

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

void		draw_map(t_lem_in *lem)
{
	int	y;
	int	x;
	int	size;
	t_room *current;

	current = NULL;
	size = (WIDTH / lem->max[1]) - ((WIDTH / lem->max[1]) / 2);
	y = -1;
	while (++y < lem->max[0])
	{
		x = -1;
		while (++x < lem->max[1])
		{
			lem->rgb = 0x66ffff;
			current = find_cords(lem, y, x);
			if (current != NULL)
			{
				if (current->type == START)
					lem->rgb = 0xffff00;
				else if (current->type == END)
					lem->rgb = 0x66ff66;
				mlx_string_put(lem->mlx, lem->win, (x * size) + (x * size), (y * size) + (y * size),
					0xFFFFFF, current->name);
				square((x * size) + (x * size), (y * size) + (y * size),
					size, lem);
			}
		}
	}
}

void		line(t_lem_in *lem, int *s, int *e)
{
	int		cath[2];
	int		overflow[2];
	int		xy[2];

	cath[0] = (e[0] - s[0]) < 0 ? (e[0] - s[0]) * -1 : (e[0] - s[0]);
	cath[1] = (e[1] - s[1]) < 0 ? (e[1] - s[1]) * -1 : (e[1] - s[1]);
	xy[0] = s[1] < e[1] ? 1 : -1;
	xy[1] = s[0] < e[0] ? 1 : -1;
	overflow[1] = cath[1] - cath[0];
	while (s[1] != e[1] || s[0] != e[0])
	{
		//if ((s[1] > 0 && s[1] < WIDTH) && (s[0] > 0 && s[0] < HEIGHT))
		mlx_pixel_put(lem->pic, lem->win, s[1], s[0], 0xff00ff);
		overflow[0] = overflow[1] * 2;
		if (overflow[0] > -cath[0])
		{
			overflow[1] -= cath[0];
			s[1] += xy[0];
		}
		else if (overflow[0] < cath[0])
		{
			overflow[1] += cath[1];
			s[0] += xy[1];
		}
	}
}

void		draw_links(t_lem_in *lem)
{
	t_link *current;
	int start[2];
	int end[2];
	int size;
	
	size = (WIDTH / lem->max[1]) - ((WIDTH / lem->max[1]) / 2);
	current = lem->links;
	while (current)
	{
		start[1] = (current->start->yx[1] * size) * 2;
		start[0] = (current->start->yx[0] * size) * 2;
		end[1] = (current->end->yx[1] * size) * 2;
		end[0] = (current->end->yx[0] * size) * 2;
		line(lem, start, end);
		current = current->next;
	}
}

int			draw(t_lem_in *lem)
{
	lem->pic = mlx_get_data_addr(lem->img, &(lem->bits_per_pixel),
		&(lem->size_line), &(lem->endian));
	background(lem);
	draw_map(lem);
	draw_links(lem);
	if (lem->pause == 1)
	{
		read_moves(lem);
	}
	mlx_put_image_to_window(lem->mlx, lem->win, lem->img, 0, 0);
	mlx_destroy_image(lem->mlx, lem->img);
	lem->img = mlx_new_image(lem->mlx, WIDTH, HEIGHT);
	return (0);
}
