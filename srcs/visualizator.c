/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 06:37:08 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/03 07:57:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include "../error_msg.h"

int		visual(t_lem_in *lem)
{
	ft_putnbr(51);
	lem->vis->mlx = mlx_init();
	lem->vis->win = mlx_new_window(lem->vis->mlx, WIDTH, HEIGHT, "Game");
	lem->vis->img = mlx_new_image(lem->vis->mlx, WIDTH, HEIGHT);
	mlx_hook(lem->vis->win, 2, 2, key_press, lem);
	draw(lem);
	lem->vis->pause = 0;
	mlx_loop_hook(lem->vis->mlx, draw, lem);
	mlx_loop(lem->vis->mlx);
	//free_map(game);
	return (0);
}
