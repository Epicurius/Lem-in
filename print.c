
#include "./lem_in.h"
/*
void	print_room(t_lem_in *lem)
{
	t_room *current;
	current = lem->rooms;
	while (current != NULL)
	{
		if (current->id == START_ID)
			ft_putstr("##start\n");
		else if (current->id == END_ID)
			ft_putstr("##end\n");
		ft_putstr(current->name);
		ft_putstr(" ID: ");
		ft_putnbr(current->id);
		ft_putchar('\n');
		current = current->next;
	}
}

void	print_table(t_lem_in *lem)
{
	int i = 0;
	while (i < lem->room_num)
	{
		printf("ID: %d, Name: %s\n", lem->id_table[i]->id, lem->id_table[i]->name);
		for (int l = 0; l < lem->id_table[i]->links_nb; l++)
			printf("\tnb: %d\n", lem->id_table[i]->links[l]);
		i++;
	}
	int y = 0;
	int x;
	while (y < lem->room_num)
	{
		x = 0;
		while (x < lem->room_num)
		{
			if (lem->links[y][x] == 1)
				printf("Link: %d-%d\n", y, x);
			x++;
		}
		y++;
	}
}

void	print_path(t_lem_in *lem, t_queue *q)
{
	int i = -1;

	printf("Len: %d, Pos: %d\n", q->len, q->position);
	while (++i < q->len && q->visited[lem->end->id] != 1 && q->queue[i] >= 0)
		printf("%d,%d->", q->queue[i], q->visited[i]);
	printf("\n");
	return ;
	i = -1;
	while (++i < lem->room_num)
	{
		int k = -1;
		while (++k < lem->room_num)
		{
			if (q->flow[i][k] == 1)
				printf("%d+%d, ", i, k);
			if (q->flow[i][k] == -1)
				printf("%d-%d, ", i, k);
		}
	}
	printf("\n");

}*/
