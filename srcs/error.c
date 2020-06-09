/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 09:32:59 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/08 09:33:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <errno.h>

void	error_msg(char *str)
{
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
