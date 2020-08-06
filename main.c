
#include "./lem_in.h"
#include "./error_msg.h"
/*
void	room_link_list(t_lem_in *lem)
{
	t_list  *links;
	t_room *curr;
	int	a;
	int	i;

	a = 0;
	i = 0;
	while (a < lem->room_nb)
	{
		if (!(lem->id_table[a]->links = ft_memalloc(sizeof(int) * (lem->id_table[a]->links_nb + 1))))
			error_msg("Id_table[i]->links malloc\n");
		i = 0;
		links = lem->id_table[a]->link;
		while (links)
		{
			curr = links->content;
			lem->id_table[a]->links[i] = curr->id;//links->content;
			i += 1;
			links = links->next;
		}
		a += 1;
	}
}*/

int main(void)
{
	t_lem_in *lem;

	lem = (t_lem_in *)malloc(sizeof(* lem));
	//ft_bzero(&lem, sizeof(lem));
	lem->end = NULL;
	lem->start = NULL;
	lem->tree = NULL;
	lem->room_nb = 2;
	read_input(lem);
	//room_link_list(lem);
	algo(lem);
	return (0);
}
