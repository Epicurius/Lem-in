/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:11:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 17:03:28 by nneronin         ###   ########.fr       */
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

void	free_lem(t_lem_in *lem)
{
	int	i;

	i = -1;
	free_tree(&lem->tree);
	while (++i < lem->max_paths)
		ft_memdel((void *)&lem->path_l.paths[i]);
	ft_memdel((void *)&lem->path_l.paths);
	ft_memdel((void *)&lem->id_table);
	free(lem);
}
