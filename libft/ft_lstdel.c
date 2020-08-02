/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:03:47 by nneronin          #+#    #+#             */
/*   Updated: 2019/10/23 17:07:40 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*first;
	t_list	*second;

	first = *alst;
	*alst = NULL;
	while (first)
	{
		second = first->next;
		del(first->content, first->content_size);
		free(first);
		first = second;
	}
}
