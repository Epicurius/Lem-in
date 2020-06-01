/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:18:03 by nneronin          #+#    #+#             */
/*   Updated: 2019/10/26 17:09:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	x;
	char	*s;

	s = (char *)str;
	x = 0;
	while (x < n)
	{
		s[x] = (char)c;
		x++;
	}
	return (str);
}
