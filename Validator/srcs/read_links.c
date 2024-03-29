/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:12:02 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/09 13:24:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../validator.h"

static void	create_link(t_env *lem, t_room *r1, t_room *r2)
{
	t_list	*node;

	node = ft_lstnew(0, 0);
	node->content = r2;
	if (!(r1->link))
	{
		r1->link = node;
		r1->flag = 0;
	}
	else
		ft_lstadd(&(r1->link), node);
	node = ft_lstnew(0, 0);
	node->content = r1;
	if (!(r2->link))
	{
		r2->link = node;
		r2->flag = 0;
	}
	else
		ft_lstadd(&(r2->link), node);
	r1->links_nb += 1;
	r2->links_nb += 1;
}

void	find_links(char *line, t_env *lem)
{
	int		nb;
	char	**arr;
	t_room	*r1;
	t_room	*r2;

	nb = 0;
	arr = ft_strpart(line, "-", &nb);
	if (nb != 2)
		error_msg("Link wrong format: %s", line);
	r1 = find_room(lem->tree, arr[0]);
	r2 = find_room(lem->tree, arr[1]);
	if (!r1)
		error_msg("No room found with name: %s.", arr[0]);
	if (!r2)
		error_msg("No room found with name: %s.", arr[1]);
	free(arr);
	create_link(lem, r1, r2);
}
