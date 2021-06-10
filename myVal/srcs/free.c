/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:59:06 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 17:00:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../validator.h"

void	free_tree(t_room **root)
{
	t_list	*tmp;

	if (!root || !*root)
		return ;
	if ((*root)->left)
		free_tree(&((*root)->left));
	if ((*root)->right)
		free_tree(&((*root)->right));
	if ((*root)->name)
		free((*root)->name);
	tmp = (*root)->link;
	while (tmp)
	{
		(*root)->link = (*root)->link->next;
		free(tmp);
		tmp = (*root)->link;
	}
	free(*root);
	*root = 0;
}

void	free_lem(t_env *lem)
{
	free_tree(&lem->tree);
	free(lem->ants);
	free(lem);
}
