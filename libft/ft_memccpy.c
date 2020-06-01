/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:46:02 by nneronin          #+#    #+#             */
/*   Updated: 2019/10/25 13:09:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			x;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	x = 0;
	while (n != 0)
	{
		s1[x] = s2[x];
		if (s1[x] == (unsigned char)c)
		{
			x++;
			return (&s1[x]);
		}
		n--;
		x++;
	}
	return (NULL);
}
