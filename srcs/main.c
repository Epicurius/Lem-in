/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 06:21:39 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/03 08:09:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include "../error_msg.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	t_lem_in *lem;

	lem = (t_lem_in *)malloc(sizeof(* lem));
	lem->end = NULL;
	lem->start = NULL;
	read_input(lem);
	print_map(lem);
	bfs_value(lem);
	trim_bfs(lem);
	align(lem);
	in_and_out(lem);
	lem->max_rout = (lem->start->paths[1] > lem->end->paths[0]
		? lem->end->paths[0] : lem->start->paths[1]);
	trim_input(lem);
	trim_output(lem);
	trim_forks(lem);
	lem->max_rout = how_many_paths(lem);
	if (lem->max_rout == 0)
		error_msg(NO_PATHS);
	create_routes(lem);
	ant_algo(lem);
	main_struct_free(lem);
	return (0);
}
