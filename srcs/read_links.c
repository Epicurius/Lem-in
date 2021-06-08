/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:12:02 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/08 19:02:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	create_link(t_lem_in *lem, t_room *r1, t_room *r2)
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

static void	connect_links(t_lem_in *lem, t_room *r1, t_room *r2)
{
	create_link(lem, r1, r2);
	if (lem->id_table[r1->id] == NULL)
		lem->id_table[r1->id] = r1;
	if (lem->id_table[r2->id] == NULL)
		lem->id_table[r2->id] = r2;
	lem->links_nb += 1;
}

void	find_links(char *line, t_lem_in *lem)
{
	int		nb;
	char	**arr;
	t_room	*r1;
	t_room	*r2;

	nb = 0;
	arr = ft_strpart(line, "-", &nb);
	if (nb != 2)
		error_msg("Link wrong format: %s", line);
	r1 = find_room(lem->tree, arr[0]); ///Here, find room should return content
	r2 = find_room(lem->tree, arr[1]);
	if (!r1)
		error_msg("No room found with name: %s.", arr[0]);
	if (!r2)
		error_msg("No room found with name: %s.", arr[1]);
	free(arr);
	connect_links(lem, r1, r2);
}
