
#include "../lem_in.h"
#include <stdio.h>
#include "../error_msg.h"

t_bfs		*create_elem(t_room *room)
{
	t_bfs	*bfs;

	if (!(bfs = (t_bfs *)ft_memalloc(sizeof(t_bfs))))
		error_msg(MALLOC_ERROR);
	bfs->room = room;
	bfs->next = NULL;
	return (bfs);
}

t_bfs		*find_strt(t_bfs **bfs)
{
	t_bfs	*elem;

	elem = NULL;
	if (bfs && *bfs)
	{
		elem = (*bfs);
		(*bfs) = (*bfs)->next;
	}
	return (elem);
}

void		connect_elem(t_bfs **bfs, t_bfs *elem)
{
	t_bfs	*current;

	if (bfs && *bfs)
	{
		current = (*bfs);
		while (current->next)
			current = current->next;
		current->next = elem;
	}
	else if (bfs)
		(*bfs) = elem;
}

void		room_links(t_lem_in *lem, t_bfs **bfs, t_room *room)
{
	t_link	*current;

	current = lem->links;
	while (current)
	{
		if (current->start == room && current->end->bfs_val == -1)
		{
			current->end->bfs_val = room->bfs_val + 1;
			connect_elem(bfs, create_elem(current->end));
		}
		else if (current->end == room && current->start->bfs_val == -1)
		{
			current->start->bfs_val = room->bfs_val + 1;
			connect_elem(bfs, create_elem(current->start));
		}
		current = current->next;
	}
}

void			bfs_value(t_lem_in *lem)
{
	t_bfs		*bfs;
	t_bfs		*current;

	bfs = NULL;
	lem->max_bfs = 0;
	lem->start->bfs_val = 0;
	connect_elem(&bfs, create_elem(lem->start));
	while (bfs != NULL)
	{
		current = find_strt(&bfs);
		if (current->room != lem->end)
		{
			room_links(lem, &bfs, current->room);
			if (current->room->bfs_val > lem->max_bfs)
				lem->max_bfs = current->room->bfs_val;
		}
		else
			lem->end->bfs_val = 2147483647;
		free(current);
	}
}
