/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:11:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/23 13:05:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
	int	i;

	i = -1;
	free_tree(&lem->tree);
	while (++i < lem->max_paths)
		ft_memdel((void *)&lem->lpath.paths[i]);
	ft_memdel((void *)&lem->lpath.paths);
	ft_memdel((void *)&lem->id_table);
	if (lem->min_moves != NULL)
		ft_memdel((void *)&lem->min_moves);
	free(lem);
}
