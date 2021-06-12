/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:23:22 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/12 13:57:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*get_room(t_list *ptr)
{
	return ((t_room *)(ptr->content));
}

void	clear_queue(t_queue *q)
{
	reset_int_array(&q->prev, q->len, -1);
	reset_int_array(&q->queue, q->len, -1);
}

void	init_queue(t_env *lem, t_queue *q)
{
	q->prev = NULL;
	q->queue = NULL;
	q->visited = NULL;
	q->len = lem->room_nb;
	q->prev = ft_memalloc(sizeof(int) * q->len);
	if (!q->prev)
		error_msg("q->prev malloc\n");
	q->queue = ft_memalloc(sizeof(int) * q->len);
	if (!q->prev)
		error_msg("q->queue malloc\n");
	q->visited = ft_memalloc(sizeof(int) * q->len);
	if (!q->visited)
		error_msg("q->visited malloc\n");
	clear_queue(q);
	reset_queue(q, START_ID, -1);
	if (lem->start->links_nb > lem->end->links_nb)
		lem->max_paths = lem->end->links_nb;
	else
		lem->max_paths = lem->start->links_nb;
	if (lem->max_paths > lem->ants)
		lem->max_paths = lem->max_paths + 1;
	else
		lem->max_paths = lem->ants + 1;
}

void	algo(t_env *lem)
{
	t_queue	q;

	init_queue(lem, &q);
	lem->lpath.paths = ft_memalloc(sizeof(t_path) * lem->max_paths);
	if (!lem->lpath.paths)
		error_msg("Malloc: lem->lpath.paths.");
	path_find(lem, &q);
	if (lem->flag.queue || lem->flag.flows)
		write(1, "\n", 1);
	if (lem->flag.format == 0 || lem->flag.format == 1)
		print_ants(lem);
	ft_memdel((void *)&q.prev);
	ft_memdel((void *)&q.queue);
	ft_memdel((void *)&q.visited);
	ft_memdel((void *)&q);
}
