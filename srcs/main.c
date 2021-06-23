/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:40:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/23 13:38:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	print_help(void)
{
	ft_printf("{CLR:41}======================HELP"
		"======================{RESET}\n");
	ft_printf("Info:\n");
	ft_printf("\t-info\t\tShows all important info.\n");
	ft_printf("\t-flows\t\tShows all posible flows.\n");
	ft_printf("\t-queue\t\tShows all bfs queues.\n");
	ft_printf("Formats:\n");
	ft_printf("\t-format=map\tShows map.\n");
	ft_printf("\t-format=ants\tShows ants movement.\n");
	ft_printf("\t-format=empty\tDoes not print anything\n");
	ft_printf("{CLR:41}==========================="
		"====================={RESET}\n");
	exit(1);
}

void	read_args(t_env *lem, int ac, char **av, int i)
{
	while (++i < ac)
	{
		if (av[i][0] == '<')
			return ;
		if (av[i][0] != '-')
			error_msg("Wrong args format.");
		else if (ft_strequ("-h", av[i]))
			print_help();
		else if (!ft_strcmp("-flows", av[i]))
			lem->flag.flows = 1;
		else if (!ft_strcmp("-info", av[i]))
			lem->flag.info = 1;
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

int	main(int ac, char **av)
{
	t_env	*lem;

	lem = (t_env *)ft_memalloc(sizeof(*lem));
	if (!lem)
		return (0);
	read_args(lem, ac, av, 0);
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
