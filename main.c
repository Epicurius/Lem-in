
#include "./lem_in.h"
#include "./error_msg.h"

void	print_table(t_lem_in *lem)
{
	int i = 0;
	while (i < lem->room_nb)
	{
		printf("ID: %d, Name: %s\n", lem->id_table[i]->id, lem->id_table[i]->name);
		for (int l = 0; l < lem->id_table[i]->links_nb; l++)
			printf("\tnb: %d\n", lem->id_table[i]->links[l]);
		i++;
	}
	int y = 0;
	int x;
	while (y < lem->room_nb)
	{
		x = 0;
		while (x < lem->room_nb)
		{
			if (lem->links[y][x] == 1)
				printf("Link: %d-%d\n", y, x);
			x++;
		}
		y++;
	}
}

int main(void)
{
	t_lem_in *lem;

	lem = (t_lem_in *)malloc(sizeof(* lem));
	lem->moves = MAX_INT;
	lem->end = NULL;
	lem->start = NULL;
	lem->room_nb = 2;
	lem->min_moves = NULL;
	read_input(lem);
	room_link_list(lem);
	if (lem->min_moves != NULL)
		fprintf(stderr, "%s\n", lem->min_moves);
	//print_table(lem);
	algo(lem);
	return (0);
}
