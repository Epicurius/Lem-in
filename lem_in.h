/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 09:19:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/23 13:23:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "libpf.h"
# include <stdio.h>
# include <time.h>
# include <stdbool.h> 
# include "error_msg.h"

# define START_ID			0
# define END_ID				1
# define MAX_INT			2147483647
# define LINES_REQUIRED		"#Here is the number of lines required:"
# define LINES_AQUIRED		"#Here is the number of lines aquired: "
# define RB_RED				1

typedef struct s_args
{
	bool			flows;
	bool			info;
	bool			queue;
	unsigned char	format;
}					t_args;

typedef struct s_queue
{
	int				*queue;
	int				*visited;
	int				*prev;
	int				position;
	int				tmp_pos;
	int				len;
}					t_queue;

typedef struct s_path
{
	int				*path;
	int				len;
	int				div;
}					t_path;

typedef struct s_lpath
{
	int				path_nb;
	int				moves;
	t_path			*paths;
}					t_lpath;

typedef struct s_room
{
	char			*name;
	struct s_room	*left;
	struct s_room	*right;
	struct s_room	*parent;
	size_t			flag;
	t_list			*link;
	size_t			links_nb;
	size_t			weight;
	int				id;
	int				y;
	int				x;
	int				ant_id;
}					t_room;

typedef struct s_lem_in
{
	char			*input;
	int				room_nb;
	int				max_paths;
	long			ants;
	long			links_nb;
	char			*min_moves;
	t_room			**id_table;
	t_room			*end;
	t_room			*start;
	t_room			*tree;
	t_lpath			lpath;
	t_args			flag;
}					t_env;

void				read_input(t_env *lem);
void				find_links(char *line, t_env *lem);
t_room				*find_room(t_room *root, char *name);
int					room_type(t_env *lem, char *line);
t_room				*new_room(t_env *lem, char *line, int id);
void				error_msg(const char *restrict format, ...);
int					rb_insert(t_room **root, t_room *node);
void				rb_balance(t_room **node, int am_i_left);
void				balance_black_uncle_left(t_room **node, int am_i_left);
void				balance_black_uncle_right(t_room **node, int am_i_left);
void				algo(t_env *lem);
//int				only_num(char *str);
void				path_find(t_env *lem, t_queue *q);
void				check_dist(t_env *lem, t_queue *q, t_room *curr,
						t_room *next);
void				check_start_end(t_env *lem, t_queue *q);
void				clear_queue(t_queue *q);
void				reset_queue(t_queue *q, int s, int e);
void				reset_int_array(int **set, int length, int n);
int					bfs(t_env *lem, t_queue *q);
int					save_paths(t_queue *q, t_env *lem, t_path *tmp);
void				add_to_queue(t_queue *q, int room, int id);
int					ant_algo(t_env *lem, int path_nb, t_path *tmp, int s);
t_room				*get_room(t_list *ptr);
t_list				*find_link(t_room *r, int e);
void				lem_free_tree(t_room **root);
//void				print_input(char **line, unsigned char i);
void				print_ants(t_env *lem);
void				print_flows(t_env *lem, t_path *tmp, int path_nb,
						int moves);
void				print_check(t_env *lem);
void				print_queue(t_env *lem, t_queue *q, int i);
t_list				*find_link(t_room *r, int e);
void				save_flow(t_queue *q, t_env *lem);
void				add_to_queue(t_queue *q, int room, int id);
void				free_paths(t_path *paths, int len);
t_room				*follow_neg_flow(t_queue *q, t_room *r, t_env *lem);
t_room				*find_neg_flow(t_queue *q, t_room *r, t_env *lem);
void				free_lem(t_env *lem);

#endif
