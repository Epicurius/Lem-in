/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 07:14:26 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/02 07:20:00 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include <stdio.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"

void		players_get(char *line, t_info *game)
{
	int		x;
	char	**tmp;
	char	**tmp2;

	x = 0;
	tmp = ft_strsplit(line, '/');
	while (ft_strstr(tmp[x], ".filler") == 0)
	{
		ft_strdel(&tmp[x]);
		x++;
	}
	tmp2 = ft_strsplit(tmp[x], '.');
	if (line[10] == '1')
		game->p1 = ft_strdup(tmp2[0]);
	else
		game->p2 = ft_strdup(tmp2[0]);
	ft_strdel(&tmp[x]);
	free(tmp);
	ft_strdel(&tmp2[0]);
	ft_strdel(&tmp2[1]);
	free(tmp2);
	ft_strdel(&line);
}

void		background(t_info *game)
{
	int	x;
	int	color;

	color = 0x363636;
	x = 0;
	while (x < (HEIGHT * WIDTH * 4))
	{
		game->pic[x] = color;
		x++;
	}
}

int			pos(int x)
{
	return ((x < 0) ? (x * -1) : x);
}

void		free_map(t_info *game)
{
	int y;

	y = 0;
	while (y < game->map_y)
	{
		free(game->map[y]);
		y++;
	}
	free(game->map);
}

int			heat_color(int value, t_info *game)
{
	int		r;
	int		g;
	int		b;
	float	ratio;

	ratio = (value - 1.0) / ((game->max - 1.0) / 2.0);
	b = 255 * (ratio - 1);
	r = 255 * (1 - ratio);
	b = b < 0 ? 0 : b;
	r = r < 0 ? 0 : r;
	g = 255 - b - r;
	g *= g < 0 ? -1 : 1;
	return ((r & 0xFF) << 16 | (g & 0xFF) | (b & 0xFF));
}
