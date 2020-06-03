/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brains.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 06:06:03 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/02 07:10:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		proximity_calc(int y, int x, t_info *game)
{
	int a;
	int b;
	int value;
	int min_value;

	a = 0;
	min_value = 2147483647;
	while (a < game->map_y)
	{
		b = 0;
		while (b < game->map_x)
		{
			if (game->map[a][b] == -2)
			{
				value = pos(a - y) + pos(b - x);
				if (value < min_value)
					min_value = value;
			}
			b++;
		}
		a++;
	}
	return (min_value);
}

int		mine_sweap(t_info *game, int y, int x)
{
	y = 0;
	game->s1 = 0;
	game->s2 = 0;
	game->max = 0;
	while (y < game->map_y)
	{
		x = 0;
		while (x < game->map_x)
		{
			if (game->map[y][x] == 0)
			{
				game->map[y][x] = proximity_calc(y, x, game);
				if (game->map[y][x] > game->max)
					game->max = game->map[y][x];
			}
			else if (game->map[y][x] == -1)
				game->s1 += 1;
			else if (game->map[y][x] == -2)
				game->s2 += 1;
			x++;
		}
		y++;
	}
	return (0);
}

int		graph_initiate(t_info *game)
{
	int y;
	int x;

	y = 0;
	while (y < Y_GRAPH)
	{
		x = 0;
		while (x < X_GRAPH)
		{
			game->graph[y][x] = 0;
			x++;
		}
		y++;
	}
	return (0);
}

int		graph(int s, int right, int p, t_info *game)
{
	int y;
	int x;
	int up;

	x = 0;
	y = Y_GRAPH;
	up = (s / ((game->map_y * game->map_x) / X_GRAPH));
	while (up-- >= 0)
	{
		y--;
	}
	while (x < right)
	{
		x++;
	}
	if (game->graph[y][x] != 0 && game->graph[y][x] != p)
		game->graph[y][x] = 3;
	else
		game->graph[y][x] = p;
	return (0);
}
