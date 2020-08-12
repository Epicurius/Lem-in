
#include "./lem_in.h"

void	print_flows(t_lem_in *lem, t_path *tmp, int path_nb, int moves)
{
	int i;

	i = 0;
	ft_putstr("~~~~~~~~~~~~~~~~~~ ");
	ft_putnbr(moves);
	ft_putstr(" ~~~~~~~~~~~~~~~~~~\n");
	while (i < path_nb)
	{
		ft_putnbr(i);
		ft_putstr(":\t");
		ft_putnbr(tmp[i].len);
		write(1, "[", 1);
		ft_putnbr(tmp[i].len);
		ft_putstr("]\n");
		i++;
	}
	ft_putstr("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void	print_check(t_lem_in *lem)
{
	ft_putstr("==================INFO==================\n");
	if (lem->min_moves != NULL)
		fprintf(stderr, "%s\n", lem->min_moves);
	ft_putstr("Moves:\t\t");
	ft_putnbr(lem->path_l.moves);
	write(1, "\n", 1);
	ft_putstr("Ants:\t\t");
	ft_putnbr(lem->ants);
	write(1, "\n", 1);
	ft_putstr("Room_nb:\t");
	ft_putnbr(lem->room_nb);
	write(1, "\n", 1);
	ft_putstr("Links_nb:\t");
	ft_putnbr(lem->links_nb);
	write(1, "\n", 1);
	ft_putstr("========================================\n");
}
