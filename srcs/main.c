/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 06:21:39 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 09:59:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include "../error_msg.h"
#include <stdio.h>

int			key_press(int key, t_lem_in *lem)
{
	if (key == 53)
	{
		mlx_destroy_image(lem->mlx, lem->img);
		main_struct_free(lem);
		exit(1);
	}
	else if (key == 35 && lem->end->ants_in != lem->ants)
	{
		lem->move += 1;
		move_everyone(lem);
		move_from_start(lem);
		draw(lem, 1);
	}
	return (0);
}

int			draw(t_lem_in *lem, int x)
{
	if (lem->enable_visuals != 1)
		return (0);
	lem->win ? mlx_clear_window(lem->mlx, lem->win) : 0;
	mlx_put_image_to_window(lem->mlx, lem->win, lem->img, 0, 0);
	x == 0 ? draw_links(lem, 0) : 0;
	draw_map(lem, x);
	return (0);
}

void		visuals(t_lem_in *lem)
{
	lem->enable_visuals = 1;
	lem->mlx = mlx_init();
	lem->win = mlx_new_window(lem->mlx, WIDTH, HEIGHT, "Network");
	lem->img = mlx_new_image(lem->mlx, WIDTH, HEIGHT);
	mlx_hook(lem->win, 2, 2, key_press, lem);
	lem->pic = mlx_get_data_addr(lem->img, &(lem->bits_per_pixel),
		&(lem->size_line), &(lem->endian));
}

void		main_part2(t_lem_in *lem)
{
	lem->move = 0;
	read_input(lem);
	lem->start->ants_in = lem->ants;
	print_map(lem);
	bfs_value(lem);
	trim_bfs(lem);
	align(lem);
	in_and_out(lem);
	lem->max_rout = (lem->start->paths[1] > lem->end->paths[0]
		? lem->end->paths[0] : lem->start->paths[1]);
	background(lem);
	draw_links(lem, 1);
	trim_input(lem);
	trim_output(lem);
	trim_forks(lem);
	lem->max_rout = how_many_paths(lem);
	draw(lem, 0);
	create_routes(lem);
}

int			main(int ac, char **av)
{
	t_lem_in *lem;

	lem = (t_lem_in *)malloc(sizeof(*lem));
	lem->end = NULL;
	lem->start = NULL;
	lem->ant_name = 1;
	lem->enable_visuals = 0;
	if (ac >= 2)
	{
		if (ft_strcmp(av[1], "-v") == 0)
			visuals(lem);
		else if (ft_strcmp(av[1], "-r") == 0)
			lem->enable_visuals = 2;
		else
			error_msg(INVALID_ARGUMENTS);
	}
	main_part2(lem);
	if (lem->enable_visuals == 1)
	{
		mlx_put_image_to_window(lem->mlx, lem->win, lem->img, 0, 0);
		mlx_loop(lem->mlx);
	}
	ant_algo(lem);
	main_struct_free(lem);
	return (0);
}
