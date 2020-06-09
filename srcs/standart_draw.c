/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standart_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 07:06:00 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 07:06:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		background(t_lem_in *lem)
{
	int	x;
	int	color;

	if (lem->enable_visuals != 1)
		return ;
	color = 0x363636;
	x = 0;
	while (x < (HEIGHT * WIDTH * 4))
	{
		lem->pic[x] = color;
		x++;
	}
}

void		pixel_rgb(char *img, int color, int x, int y)
{
	img[0 + (x * WIDTH * 4) + (y * 4)] = color;
	img[1 + (x * WIDTH * 4) + (y * 4)] = color >> 8;
	img[2 + (x * WIDTH * 4) + (y * 4)] = color >> 16;
	img[3 + (x * WIDTH * 4) + (y * 4)] = 0;
}

void		line(t_lem_in *lem, int *s, int *e)
{
	int		xy[2];
	int		cath[2];
	int		overflow[2];

	cath[0] = (e[0] - s[0]) < 0 ? (e[0] - s[0]) * -1 : (e[0] - s[0]);
	cath[1] = (e[1] - s[1]) < 0 ? (e[1] - s[1]) * -1 : (e[1] - s[1]);
	xy[0] = s[1] < e[1] ? 1 : -1;
	xy[1] = s[0] < e[0] ? 1 : -1;
	overflow[1] = cath[1] - cath[0];
	while (s[1] != e[1] || s[0] != e[0])
	{
		pixel_rgb(lem->pic, lem->rgb, s[0], s[1]);
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
