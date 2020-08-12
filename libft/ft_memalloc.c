/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:49:46 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/12 14:26:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
/*
void	*ft_memalloc(size_t size)
{
	char *str;

	if (!(str = (void *)malloc(sizeof(size_t) * (size))))
		return (0);
	ft_bzero(str, size);
	return (str);
}*/
void		*ft_memalloc(size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(size);
	if (!ptr)
	{
		return (ptr);
	}
	while (i < size)
	{
		((char*)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
