/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:15:03 by nneronin          #+#    #+#             */
/*   Updated: 2020/09/24 17:15:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <stdio.h>

int		ant_move_calc(t_path *tmp, int i)
{
	int x;
	int k;

	k = 0;
	x = 0;
	while (k != i)
	{
		x += (tmp[i].len - tmp[k].len);
		k += 1;
	}
	return (x);
}

void		move_from_start(t_path *tmp, int j, int *ants)
{
	int i = 0;

	while (i < j && *ants > 0)
	{
		if (*ants > ant_move_calc(tmp, i))
		{
			*ants -= 1;
			tmp[i].div += 1;
		}
		i++;
	}
}

int	ant_algo(t_lem_in *lem, int path_nb, t_path *tmp, int s)
{
	int max_ants;
	int c;

	c = 0;
	max_ants = lem->ants;
	while (max_ants > 0)
	{
		move_from_start(tmp, path_nb, &max_ants);
		c += 1;
	}
	if (lem->flag.flows == 1)
		print_flows(lem, tmp, path_nb, (c + (s - 1)));
	return (c += (s - 1));
}
