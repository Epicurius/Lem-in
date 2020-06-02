/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 08:32:55 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/02 09:29:31 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <stdio.h>

void	input_copy(t_lem_in *lem, char *line)
{
	char *tmp;
	char *tmp2;

	if (lem->org_input != NULL)
	{
		tmp = ft_strdup(lem->org_input);
		free(lem->org_input);
		tmp2 = ft_strjoin(line, "\n");
		lem->org_input = ft_strjoin(tmp, tmp2);
		free(tmp2);
		free(tmp);
	}
	else
	{
		tmp2 = ft_strjoin(line, "\n");
		lem->org_input = ft_strdup(tmp2);
		free(tmp2);
	}
}
