/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:36:26 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/04 11:55:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vis.h"
#include <stdio.h>

int	read_moves(t_lem_in *lem)
{
	char *line;
	char *moves;
	t_room *current;
	int x;
	
	x = 0;
	line = NULL;
	ant_num;
	while (get_next_line(0, &line) > 0)
	{
		moves = ft_strdslit(line, ' ');
		while (moves[x])
		{
			current = find_room(after "-");
			current->ant = ant_num;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(line);
	return (0);
}
