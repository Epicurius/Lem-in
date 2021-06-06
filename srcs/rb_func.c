/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 11:05:55 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/06 09:37:20 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static inline void	simplify_to_right(t_room **node)
{
	t_room	*tmp;

	tmp = (*node)->right;
	if (tmp)
		tmp->parent = (*node)->parent;
	(*node)->right = (*node)->parent;
	(*node)->parent = (*node)->parent->parent;
	(*node)->parent->right = *node;
	(*node)->right->parent = *node;
	(*node)->right->left = tmp;
}

void	balance_black_uncle_right(t_room **node, int am_i_left)
{
	t_room	*tmp;

	if (am_i_left)
		simplify_to_right(node);
	if (!am_i_left)
		*node = (*node)->parent;
	(*node)->flag &= ~RB_RED;
	(*node)->parent->flag |= RB_RED;
	tmp = (*node)->left;
	if (tmp)
		tmp->parent = (*node)->parent;
	(*node)->left = (*node)->parent;
	(*node)->left->right = tmp;
	(*node)->parent = (*node)->left->parent;
	(*node)->left->parent = *node;
	if (!((*node)->parent))
		return ;
	if ((*node)->parent->left == (*node)->left)
		(*node)->parent->left = *node;
	else
		(*node)->parent->right = *node;
}

static inline void	simplify_to_left(t_room **node)
{
	t_room	*tmp;

	tmp = (*node)->left;
	if (tmp)
		tmp->parent = (*node)->parent;
	(*node)->left = (*node)->parent;
	(*node)->parent = (*node)->parent->parent;
	(*node)->parent->left = *node;
	(*node)->left->parent = *node;
	(*node)->left->right = tmp;
}

void	balance_black_uncle_left(t_room **node, int am_i_left)
{
	t_room	*tmp;

	if (!am_i_left)
		simplify_to_left(node);
	if (am_i_left)
		*node = (*node)->parent;
	(*node)->flag &= ~RB_RED;
	(*node)->parent->flag |= RB_RED;
	tmp = (*node)->right;
	if (tmp)
		tmp->parent = (*node)->parent;
	(*node)->right = (*node)->parent;
	(*node)->right->left = tmp;
	(*node)->parent = (*node)->right->parent;
	(*node)->right->parent = *node;
	if (!((*node)->parent))
		return ;
	if ((*node)->parent->left == (*node)->right)
		(*node)->parent->left = *node;
	else
		(*node)->parent->right = *node;
}
