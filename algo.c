/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:23:22 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/14 11:45:40 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room				*get_room(t_list *ptr)
{
	return ((t_room *)(ptr->content));
}

void	clear_queue(t_queue *q)
{
	reset_int_array(&q->prev, q->len, -1);
	reset_int_array(&q->queue, q->len, -1);
}

void	init_queue(t_lem_in *lem, t_queue *q)
{
	int	a;
	int b;

	q->prev = NULL;
	q->queue = NULL;
	q->visited = NULL;
	q->len = lem->room_nb;
	if (!(q->prev = ft_memalloc(sizeof(int) * q->len)))
		error_msg("q->prev malloc\n");
	if (!(q->queue = ft_memalloc(sizeof(int) * (q->len + 10))))
		error_msg("q->queue malloc\n");
	if (!(q->visited = ft_memalloc(sizeof(int) * q->len)))
		error_msg("q->visited malloc\n");
	clear_queue(q);
	reset_queue(q, START_ID, -1);
	a = lem->start->links_nb;
	b = lem->end->links_nb;
	lem->max_paths = a > b ? b : a;
	lem->max_paths = lem->max_paths < lem->ants ? lem->max_paths + 1 : lem->ants + 1;
}

void	algo(t_lem_in *lem)
{
	t_queue q;

	init_queue(lem, &q);
	if (!(lem->path_l.paths = ft_memalloc(sizeof(t_path) * (lem->max_paths))))
		error_msg("Malloc: lem->path_l.paths.");
	path_find(lem, &q);

	/*
	int i = 0;
	while (lem->id_table[i])
	{
		t_list *link = lem->id_table[i]->link;
		printf("Name:%s\n", lem->id_table[i]->name);
		while (link)
		{
			printf("\t%s, %zu", get_room(link)->name, link->content_size);
			link = link->next;
		}
		printf("\n");
		i += 1;
	}*/
	/*
	int k = -1;
	while (++k < 2)
	{
		int p = -1;
		printf("(%d)\t", lem->path_l.paths[k].len);
		while (++p < lem->path_l.paths[k].len)
			printf("%s ", lem->id_table[lem->path_l.paths[k].path[p]]->name);
		printf("\n");
	}*/

	if (lem->flag.format == 0 || lem->flag.format == 1)
		print_ants(lem);
	ft_memdel((void*)&q.prev);
	ft_memdel((void*)&q.queue);
	ft_memdel((void*)&q.visited);
	ft_memdel((void*)&q);
}
