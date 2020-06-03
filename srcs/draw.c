/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 06:47:05 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/03 07:53:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include "../error_msg.h"

void		square(int s_x, int s_y, int size, t_lem_in *lem)
{
	int		y;
	int		x;
	int		tmp;

	y = 0;
	tmp = 0;
	int rgb = 0xff00ff;
	while (y < (size * 4))
	{
		x = 0;
		while (x < (size * 4))
		{
			lem->vis->pic[x + tmp + ((s_y * WIDTH * 4) + (s_x * 4))] =
				rgb;
			lem->vis->pic[x + 1 + tmp + ((s_y * WIDTH * 4) + (s_x * 4))] =
				rgb >> 8;
			lem->vis->pic[x + 2 + tmp + ((s_y * WIDTH * 4) + (s_x * 4))] =
				rgb >> 16;
			x += 4;
		}
		y += 4;
		tmp += (WIDTH * 4);
	}
}

void		draw_map(t_lem_in *lem)
{
	int	y;
	int	x;
	int	size;
	int	offset;

	size = ((WIDTH / 2) / (lem->max[1])) - 2;
	offset = ((HEIGHT - (lem->max[0] * size) - (lem->max[0] * 2)) / 2);
	y = -1;
	while (++y < lem->max[0])
	{
		x = -1;
		while (++x < lem->max[1])
		{
			square((x * size) + (x * 2) + 2, (y * size) + (y * 2) + offset,
				size, lem);
		}
	}
}

void		background(t_lem_in *lem)
{
	int	x;
	int	color;

	color = 0x363636;
	x = 0;
	while (x < (HEIGHT * WIDTH * 4))
	{
		lem->vis->pic[x] = color;
		x++;
	}
}

int			draw(t_lem_in *lem)
{
		lem->vis->pic = mlx_get_data_addr(lem->vis->img, &(lem->vis->bits_per_pixel),
			&(lem->vis->size_line), &(lem->vis->endian));
		background(lem);
		//draw_map(lem);
		mlx_put_image_to_window(lem->vis->mlx, lem->vis->win, lem->vis->img, 0, 0);
		mlx_destroy_image(lem->vis->mlx, lem->vis->img);
		lem->vis->img = mlx_new_image(lem->vis->mlx, WIDTH, HEIGHT);
	return (0);
}
