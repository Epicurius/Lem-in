
#include "lem_in.h"

char	*ft_strndup(const char *s1, ssize_t len)
{
	ssize_t	counter;
	char	*sdest;

	counter = 0;
	if (!(sdest = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[counter] != '\0' && counter < len)
	{
		sdest[counter] = s1[counter];
		counter++;
	}
	sdest[counter] = '\0';
	return (sdest);
}
/*
void	room_link_list(t_lem_in *lem)
{
	int	a;
	int	b;
	int	i;

	a = 0;
	b = 0;
	i = 0;
	while (a < lem->room_nb)
	{
		if (!(lem->id_table[a]->links = ft_memalloc(sizeof(int) * (lem->id_table[a]->links_nb + 1))))
			error_msg("Id_table[i]->links malloc\n");
		while (b < lem->room_nb)
		{
			if (lem->links[a][b] == 1)
			{
				lem->id_table[a]->links[i] = b;
				i += 1;
			}
			b += 1;
		}
		a += 1;
		b = 0;
		i = 0;
	}
}*/
