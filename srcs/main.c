/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:40:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 16:15:42 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	read_args(t_lem_in *lem, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '<')
			return ;
		if (av[i][0] != '-')
			error_msg("Wrong args format.");
		else if (!ft_strcmp("-flows", av[i]))
			lem->flag.flows = 1;
		else if (!ft_strcmp("-info", av[i]))
			lem->flag.info = 1;
		else if (!ft_strcmp("-full", av[i]))
			lem->flag.full = 1;
		else if (!ft_strcmp("-queue", av[i]))
			lem->flag.queue = 1;
		else if (!ft_strcmp("-format=ants", av[i]))
			lem->flag.format = 1;
		else if (!ft_strcmp("-format=map", av[i]))
			lem->flag.format = 2;
		else if (!ft_strcmp("-format=empty", av[i]))
			lem->flag.format = 3;
	}
}

int	main1(int ac, char **av)
{
	t_lem_in	*lem;

	lem = (t_lem_in *)ft_memalloc(sizeof(*lem));
	read_args(lem, ac, av);
	lem->room_nb = 2;
	lem->links_nb = 0;
	read_input(lem);
	if (lem->ants == 0)
		return (0);
	if (lem->flag.format == 0 || lem->flag.format == 2)
		write(1, "\n", 1);
	algo(lem);
	if (lem->flag.info == 1)
		print_check(lem);
	free_lem(lem);
	return (0);
}

int	main(int ac, char **av)
{
	main1(ac, av);
	//while (1)
	//	;
	return (1);
}
