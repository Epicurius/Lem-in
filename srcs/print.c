/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:39:24 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/08 10:39:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	print_route(t_lem_in *lem, int len)
{
	t_route	*current;
	t_link	*current1;

	current = lem->routes;
	while (current != NULL)
	{
		current1 = current->strt;
		len = 0;
		ft_putchar('[');
		while (current1)
		{
			len += 1;
			ft_putstr(current1->start->name);
			ft_putstr("]->[");
			if (!current1->next)
			{
				ft_putstr(current1->end->name);
				ft_putstr("]	Length: ");
				ft_putnbr(len);
			}
			current1 = current1->next;
		}
		ft_putstr("\n");
		current = current->next;
	}
}

void	print_map(t_lem_in *lem)
{
	ft_putstr(lem->org_input);
	ft_strdel(&lem->org_input);
	free(lem->org_input);
	ft_putstr("\n");
}
