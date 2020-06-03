/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 07:17:06 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/03 09:50:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "../libft/get_next_line.h"

int		key_press(int key, t_lem_in *lem)
{
	if (key == 53)
		exit(1);
	else if (key == 35)
		lem->pause = lem->pause == 0 ? 1 : 0;
	return (0);
}

int		main(void)
{
	t_lem_in		*lem;

	lem = (t_lem_in *)malloc(sizeof(*lem));
	lem->end = NULL;
	lem->start = NULL;
	read_input(lem);
	lem->pause = 0;
	lem->mlx = mlx_init();
	lem->win = mlx_new_window(lem->mlx, WIDTH, HEIGHT, "Game");
	lem->img = mlx_new_image(lem->mlx, WIDTH, HEIGHT);
	mlx_hook(lem->win, 2, 2, key_press, lem);
	draw(lem);
	lem->pause = 1;
	mlx_loop_hook(lem->mlx, draw, lem);
	mlx_loop(lem->mlx);
	//free_map(game);
	return (0);
}
