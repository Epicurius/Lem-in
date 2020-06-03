/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 06:03:08 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/02 07:10:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		graph_print(t_info *game)
{
	int y;
	int x;

	y = 0;
	while (y < 30)
	{
		x = 0;
		while (x < 60)
		{
			ft_putnbr(game->graph[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	return (0);
}

int		key_press(int key, t_info *game)
{
	if (key == 53)
		exit(1);
	else if (key == 35)
		game->pause = game->pause == 0 ? 1 : 0;
	else if (key == 4)
	{
		game->heat = game->heat == 0 ? 1 : 0;
		mine_sweap(game, 0, 0);
		background(game);
		draw_map(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
		mlx_destroy_image(game->mlx, game->img);
		game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	}
	return (0);
}
