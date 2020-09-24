
#include "../lem_in.h"
#include <errno.h>
#include <stdio.h>

void		error_msg(char *str)
{
	if (errno != 0)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	exit(0);
}

int		only_num(char *str)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] < 48 || str[x] > 57)
			return (0);
		x++;
	}
	return (1);
}
