/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 11:06:49 by nneronin          #+#    #+#             */
/*   Updated: 2020/08/05 16:53:31 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lem_in.h"
#include "./error_msg.h"
#include <stdio.h>

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

static void	print_input(char **line)
{
	//ft_putstr(*line);
	//write(1, "\n", 1);
	ft_strdel(line);
}

t_room 	*new_room(t_lem_in *lem, char *line, int id)
{
	char **tmp;
	t_room *room;
	
	tmp = ft_strsplit(line, ' ');
	if (tmp[0] && tmp[1] == NULL)
	{
		lem->room_nb -= 1;
		return (NULL);
	}
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL)
		error_msg(EXTRA_CRAP);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(tmp[0]);
	room->y = ft_atoi(tmp[2]);
	room->x = ft_atoi(tmp[1]);
	room->left = NULL;
	room->right = NULL;
	room->parent = NULL;
	room->links_nb = 0;
	room->weight = 0;
	room->flag = RB_RED;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	ft_strdel(&tmp[2]);
	free(tmp);
	if (id == START_ID)
		lem->start = room;
	else if (id == END_ID)
		lem->end = room;
	room->id = id;
	return (room);

}

static t_type	room_type(t_lem_in *lem, char *line)
{
	int i;

	if (line[0] == '#')
	{
		if (!ft_strcmp(line, "##start"))
			return (START_ID);
		else if (!ft_strcmp(line, "##end"))
			return (END_ID);
		else
			return (-1);
	}
	if (line[0] == 'L')
		error_msg(L_START);
	return (lem->room_nb++);
}

static inline int	launch_recursive(t_room **root, t_room **node)
{
	int	val;

	//if ((*root) != NULL)
	//	printf("%s ", (*root)->name);
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
	//printf("(%s) ", node->name);
	if (launch_recursive(root, &node) == -1)
		return (-1);
	//printf("\n");
	rb_balance(&node, (node->parent && node->parent->left == node ? 1 : 0));
	while (node->parent != NULL)
		node = node->parent;
	*root = node;
	(*root)->flag &= ~RB_RED;
	return (0);
}

t_room	*find_room(t_room *root, char *name)
{
	int	val;
	t_room	*node;

	node = root;
	while (1)
	{
		if (!node)
			return (NULL);
		val = ft_strcmp(node->name, name);
		if (val == 0)
			return (node);
		node = val > 0 ? node->left : node->right;
	}
	return (NULL);
}

void	create_link(t_room *left, t_room *right)
{
	t_list	*node;

	if (!(node = ft_lstnew(0, 0)))
		error_msg("Malloc node.");
	node->content = right;
	if (!(left->link))
	{
		left->link = node;
		left->flag = 0;
	}
	else
		ft_lstadd(&(left->link), node);
	if (!(node = ft_lstnew(0, 0)))
		error_msg("Malloc node.");
	node->content = left;
	if (!(right->link))
	{
		right->link = node;
		right->flag = 0;
	}
	else
		ft_lstadd(&(right->link), node);
	left->links_nb += 1;
	right->links_nb += 1;
}

int	find_links(char *line, t_lem_in *lem)
{
	char *strt;
	char *end;
	int len;
	t_room *start_room;
	t_room *end_room;

	len = 0;
	while (line[len] != '-' && line[len] != '\0')
		len++;
	strt = ft_strndup(line, len);
	line = ft_strchr(line, '-') + 1;
	len = 0;
	while (line[len] != '\0')
		len++;
	end = ft_strndup(line, len);
	start_room = find_room(lem->tree, strt);
	end_room = find_room(lem->tree, end);
	free(strt);
	free(end);
	if (start_room && end_room)
	{
		create_link(start_room, end_room);
		if (lem->id_table[start_room->id] == NULL)
			lem->id_table[start_room->id] = start_room;
		if (lem->id_table[end_room->id] == NULL)
			lem->id_table[end_room->id] = end_room;
	}
	else
	{
		error_msg("No room found with that name.");
	}
	return (0);
}


int	read_links(char *line, t_lem_in *lem)
{
	find_links(line, lem);
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] != '#')
			find_links(line, lem);
		print_input(&line);
	}
	return (0);
}

char	*read_rooms(char *line, t_lem_in *lem)
{
	t_room *room;
	int id;

	while (get_next_line(0, &line))
	{
		id = room_type(lem, line);
		if (id == START_ID || id == END_ID)
		{
			print_input(&line);
			get_next_line(0, &line);
			room = new_room(lem, line, id);
			rb_insert((&lem->tree), room);
		}
		else if (id != -1)
		{
			if ((room = new_room(lem, line, id)) == NULL)
				return (line);
			rb_insert((&lem->tree), room);
		}
		if (lem->min_moves == NULL && ft_strstr(line, LINES_REQUIRED))
			lem->min_moves = ft_strdup(line);
		print_input(&line);
	}
	return (NULL);
}

void	read_ants(t_lem_in *lem, char *line)
{
	while (get_next_line(0, &line))
	{
		if (!(line[0] == '#' && line[1] != '#'))
		{
			lem->ants = ft_atoi(line);
			print_input(&line);
			if (lem->ants > 2147483647 || lem->ants <= 0)
				error_msg(WRONG_ANT_AMOUNT);
			return ;
		}
		print_input(&line);
	}
}

void	read_input(t_lem_in *lem)
{
	char *line;

	line = NULL;
	lem->min_moves = NULL;
	read_ants(lem, line);
	line = read_rooms(line, lem);
	if (lem->end == NULL || lem->start == NULL)
		error_msg(MISSING_ROOM);
	if (lem->min_moves != NULL)
		fprintf(stderr, "%s\n", lem->min_moves);
	if (!(lem->id_table = ft_memalloc(sizeof(t_room *) * (lem->room_nb + 1))))
		error_msg("Id_table malloc\n");
	read_links(line, lem);
	free(line);
}
