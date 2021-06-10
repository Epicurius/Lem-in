/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:40:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 17:08:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../validator.h"

int	check_ant_curr_room_links(t_env *lem, int ant, t_room *room)
{
	t_list	*curr;

	curr = lem->ants[ant]->link;
	while (curr)
	{
		if (ft_strequ(((t_room *)curr->content)->name, room->name))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	move_ants(t_env *lem, char **arr2)
{
	t_room	*room;
	int		ant;

	room = find_room(lem->tree, arr2[1]);
	if (room == NULL)
		error_msg("Room %s dose not exist.", arr2[1]);
	if (room != lem->end && room->ant != 0)
		error_msg("Ants overlap in room %s.", arr2[1]);
	ant = ft_atoi(arr2[0]);
	if (ant <= 0 || ant > lem->ant_nb)
		error_msg("Ant %s is not a real ant.", arr2[1]);
	if (!check_ant_curr_room_links(lem, ant, room))
		error_msg("Ant %s cant travel to room %s.", arr2[0], arr2[1]);
	if (lem->ants[ant] == lem->start)
	{
		if (lem->start_nb <= 0)
			error_msg("No more ants left in start.");
		lem->start_nb -= 1;
	}
	if (room == lem->end)
		lem->end_nb += 1;
	lem->ants[ant]->ant = 0;
	lem->ants[ant] = room;
	lem->ants[ant]->ant = ant;
}

void read_cmd(t_env *lem)
{
	int		i;
	int		nb1;
	int		nb2;
	char	*line;
	char	**arr1;
	char	**arr2;

	while (get_next_line(0, &line) && lem->end_nb < lem->ant_nb)
	{
		i = -1;
		arr1 = ft_strsplit(line, ' ', &nb1);
		while (++i < nb1)
		{
			arr2 = ft_strpart(&arr1[i][1], "-", &nb2);
			move_ants(lem, arr2);
			free(arr2);
		}
		free(arr1);
		free(line);
	}

}

int	main(int ac, char **av)
{
	t_env	*lem;

	lem = (t_env *)ft_memalloc(sizeof(*lem));
	lem->room_nb = 2;
	read_input(lem);
	int i = 0;
	while (++i <= lem->ant_nb)
		lem->ants[i] = lem->start;
	lem->end_nb = 0;
	lem->start_nb = lem->ant_nb;
	read_cmd(lem);
	i = 0;
	while (++i <= lem->ant_nb)
		if (lem->ants[i] != lem->end)
			error_msg("All ant didnt find end");
	ft_printf("{GREEN}[OK]{RESET}\n");
	free_lem(lem);
	return (0);
}
