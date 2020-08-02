
#include "lem_in.h"

void	clear_queue(t_queue *q)
{
	reset_int_array(&q->prev, q->len, -1);
	reset_int_array(&q->queue, q->len, -1);
}

void	init_queue(t_lem_in *lem, t_queue *q)
{
	int i;

	i = 0;
	q->len = lem->room_nb + 10;
	q->queue = NULL;
	q->prev = NULL;
	q->flow = NULL;
	q->visited = NULL;
	if (!(q->queue = ft_memalloc(sizeof(int) * q->len)))
		error_msg("q->queue malloc\n");
	if (!(q->prev = ft_memalloc(sizeof(int) * q->len)))
		error_msg("q->prev malloc\n");
	if (!(q->visited = ft_memalloc(sizeof(int) * q->len)))
		error_msg("q->visited malloc\n");
	if (!(q->flow = ft_memalloc(sizeof(int *) * q->len)))
		error_msg("q->flow[] malloc\n");
	while (i < q->len)
	{
		if (!(q->flow[i++] = ft_memalloc(sizeof(int) * q->len)))
			error_msg("q->flow[][] malloc\n");
	}
	clear_queue(q);
	reset_queue(q, START_ID, -1);
}

void	start_kick(t_lem_in *lem, t_path *p, int *name)
{
	t_path *curr;

	curr = p;
	while (curr)
	{
		if (curr->move > 0)
		{
			printf("L%d-%s ", *name, lem->id_table[curr->path[1]]->name);
			lem->id_table[curr->path[1]]->ant_id = *name;
			*name += 1;
			curr->move -= 1;
		}
		curr = curr->next;
	}
	printf("\n");
}

void	move_along(t_lem_in *lem, t_path *p, int *end_ants)
{
	t_path *curr;
	int i = 1;

	curr = p;
	while (curr)
	{
		i = curr->len - 1;
		while (i > 0)
		{
			if (lem->id_table[curr->path[i]]->ant_id != 0)
			{
				printf("L%d-%s ", lem->id_table[curr->path[i]]->ant_id,
						lem->id_table[curr->path[i + 1]]->name);
				lem->id_table[curr->path[i + 1]]->ant_id = 
					lem->id_table[curr->path[i]]->ant_id;
				lem->id_table[curr->path[i]]->ant_id = 0;
				if (lem->id_table[curr->path[i + 1]]->id == END_ID)
					*end_ants += 1;
			}
			i -= 1;
		}
		curr = curr->next;
	}
}

void	algo(t_lem_in *lem)
{
	t_queue q;
	t_path *p;

	init_queue(lem, &q);
	path_find(lem, &q, &p);
	int end_ants = 0;
	int name = 1;

	t_path *curr;
	while (end_ants < lem->ants)
	{
		move_along(lem, p, &end_ants);
		start_kick(lem, p, &name);
	}
	//ft_putnbr_fd(p->llen, 2);
}
