#ifndef LEM_IN_H
# define LEM_IN_H

# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# include <stdio.h>
# define START_ID 0
# define END_ID 1
# define MAX_INT 2147483647
# define LINES_REQUIRED "#Here is the number of lines required:"
# define RB_RED 1

typedef enum
{
	START,
	MIDDLE,
	END,
	COMMENT
}	t_type;


//typedef struct			s_tree_data
//{
//	char				*line;
//	size_t				fin;
//	long long			x;
//	long long			y;
//}						t_tree_data;

typedef struct		s_queue
{
	int				*queue;
	int				*visited;
	int				*prev;
	int				len;
	int				position;
	int				**flow;
}					t_queue;

typedef struct		s_path
{
	int				len;
	int				*path;
	int				path_nb;
	int				move;
	int				*div;
	int				llen;
	struct s_path	*next;
}					t_path;

typedef struct			s_room
{
	struct s_room		*left;
	struct s_room		*right;
	struct s_room		*parent;
	int					x;
	int					y;
	size_t				flag;
	size_t				links_nb;
	size_t				visited;
	int				weight;
	char				*name;
	int					id;
	int					ant_id;
	t_list				*link;
}						t_room;

typedef	struct		s_lem_in
{
	int				max_paths;
	int				moves;
	long			ants;
	int				links_nb;
	int				room_nb;
	char			*min_moves;
	int				**links;
	t_room			**id_table;
	t_room			*end;
	t_room			*start;
	t_room			*tree;
}					t_lem_in;

void				read_input(t_lem_in *lem);
void				error_msg(char *str);
char				*ft_strndup(const char *s1, ssize_t len);
void	balance_black_uncle_left(t_room **node, int am_i_left);
void	balance_black_uncle_right(t_room **node, int am_i_left);
void				algo(t_lem_in *lem);
int					only_num(char *str);
void				print_table(t_lem_in *lem);
void				print_map(t_lem_in *lem);
void				room_link_list(t_lem_in *lem);
void				path_find(t_lem_in *lem, t_queue *q, t_path **p);
void				free_path(t_path *path_list);
void				check_dist(t_lem_in *lem, t_queue *q, t_room *curr, t_room *next);
void				check_start_end(t_lem_in *lem, t_queue *q);
void				clear_queue(t_queue *q);
void				reset_queue(t_queue *q, int s, int e);
void				set_max_weights(t_lem_in *lem);
t_path				*create_paths(int *path, int len);
void				reset_int_array(int **set, int length, int n);
void				add_path_to_list(t_path *paths, t_path *new);
int					bfs(t_lem_in *lem, t_queue *q);
void				save_paths(t_queue *q, t_lem_in *lem, t_path **path_list);
void				set_path(t_path **path_list, int i, t_lem_in *lem);
void				add_to_queue(t_queue *q, int room, int id);
void				ant_algo(t_lem_in *lem, t_path *path_l);


#endif
