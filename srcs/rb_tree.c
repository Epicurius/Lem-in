/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:11:02 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/06 09:49:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	lem_free_tree(t_room **root)
{
	t_list	*tmp;

	if (!root || !*root)
		return ;
	if ((*root)->left)
		lem_free_tree(&((*root)->left));
	if ((*root)->right)
		lem_free_tree(&((*root)->right));
	if ((*root)->name)
		free((*root)->name);
	tmp = (*root)->link;
	if (tmp)
	{
		while (tmp)
		{
			(*root)->link = (*root)->link->next;
			free(tmp);
			tmp = (*root)->link;
		}
	}
	free(*root);
	*root = 0;
}

void	rb_balance(t_room **node, int am_i_left)
{
	t_room	*uncle;
	t_room	*parent;
	int		is_parent_left;

	parent = (*node)->parent;
	if (!parent)
		(*node)->flag &= ~RB_RED;
	if (!parent || !(parent->flag & RB_RED))
		return ;
	is_parent_left = (parent->parent && parent->parent->left == parent);
	if (is_parent_left)
		uncle = parent->parent->right;
	else
		uncle = parent->parent->left;
	if (uncle && uncle->flag & RB_RED)
	{
		parent->flag &= ~RB_RED;
		uncle->flag &= ~RB_RED;
		parent->parent->flag |= RB_RED;
		parent = parent->parent;
		is_parent_left = (parent->parent && parent->parent->left == parent);
		rb_balance(&parent, is_parent_left);
	}
	else if (is_parent_left)
		balance_black_uncle_left(node, am_i_left);
	else
		balance_black_uncle_right(node, am_i_left);
}

static inline int	launch_recursive(t_room **root, t_room **node)
{
	int	val;

	if ((*root) == NULL)
	{
		(*root) = *node;
		return (0);
	}
	val = ft_strcmp((*root)->name, (*node)->name);
	if (!val)
		return (-1);
	else if (val > 0 && (*root)->left)
		return (launch_recursive(&((*root)->left), node));
	else if (val < 0 && (*root)->right)
		return (launch_recursive(&((*root)->right), node));
	else if (val > 0)
		(*root)->left = *node;
	else
		(*root)->right = *node;
	(*node)->parent = (*root);
	return (0);
}

int	rb_insert(t_room **root, t_room *node)
{
	if (!root || !node)
		return (-1);
	if (launch_recursive(root, &node) == -1)
		return (-1);
	if (node->parent && node->parent->left == node)
		rb_balance(&node, 1);
	else
		rb_balance(&node, 0);
	while (node->parent != NULL)
		node = node->parent;
	*root = node;
	(*root)->flag &= ~RB_RED;
	return (0);
}
