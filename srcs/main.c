
#include "../lem_in.h"
#include "../error_msg.h"

//print_length(lem);

void	read_args(t_lem_in *lem, int ac, char **av)
{
	int i = 0;

	lem->flag.full = 0;
	lem->flag.flows = 0;
	lem->flag.info = 0;
	lem->flag.queue = 0;
	lem->flag.format = 0;
	while (++i < ac)
	{
		if (av[i][0] == '<')
			return ;
		if (av[i][0] != '-')
			error_msg("ERROR: Wrong args format.");
		else if (!ft_strcmp("-flows", av[i]))
			lem->flag.flows = 1;
		else if (!ft_strcmp("-info", av[i]))
			lem->flag.info = 1;
		else if (!ft_strcmp("-full", av[i]))
			lem->flag.full = 1;
		else if (!ft_strcmp("-queue", av[i]))
			lem->flag.queue = 1;
		else if (!ft_strcmp("-format=ants", av[i]))
			lem->flag.format = 1;
		else if (!ft_strcmp("-format=map", av[i]))
			lem->flag.format = 2;
		else if (!ft_strcmp("-format=empty", av[i]))
			lem->flag.format = 3;
	}
}

int main(int ac, char **av)
{
	t_lem_in *lem;

	lem = (t_lem_in *)malloc(sizeof(* lem));
	read_args(lem, ac, av);
	lem->start = NULL;
	lem->tree = NULL;
	lem->end = NULL;
	lem->room_nb = 2;
	lem->links_nb = 0;
	read_input(lem);
	if (lem->flag.format == 0 || lem->flag.format == 2)
		write(1, "\n", 1);
	algo(lem);
	if (lem->flag.info == 1)
		print_check(lem);
	lem_free_tree(&lem->tree);
	ft_memdel((void*)&lem->id_table);
	free(lem);
	return (0);
}

