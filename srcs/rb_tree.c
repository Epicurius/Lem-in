/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:11:02 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/12 17:10:00 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void					lem_free_tree(t_room **root)
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
	if ((tmp = (*root)->link))
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

void				rb_balance(t_room **node, int am_i_left)
{
	t_room	*uncle;
	t_room	*parent;
	int		is_parent_left;

	parent = (*node)->parent;
	if (!parent)
		(*node)->flag &= ~RB_RED;
	if (!parent || !(parent->flag & RB_RED))
		return ;
	is_parent_left = parent->parent && parent->parent->left == parent ? 1 : 0;
	uncle = is_parent_left ? parent->parent->right : parent->parent->left;
	if (uncle && uncle->flag & RB_RED)
	{
		parent->flag &= ~RB_RED;
		uncle->flag &= ~RB_RED;
		parent->parent->flag |= RB_RED;
		parent = parent->parent;
		is_parent_left = (parent->parent && parent->parent->left == parent) ? 1 : 0;
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
	else if (!(val = ft_strcmp((*root)->name, (*node)->name)))
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
	rb_balance(&node, (node->parent && node->parent->left == node ? 1 : 0));
	while (node->parent != NULL)
		node = node->parent;
	*root = node;
	(*root)->flag &= ~RB_RED;
	return (0);
}
