#ifndef LEM_IN_H
# define LEM_IN_H

# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# include <stdio.h>
# define START_ID 0
# define END_ID 1
# define MAX_INT 2147483647

typedef enum
{
	START,
	MIDDLE,
	END,
	COMMENT
}	t_type;

typedef struct		s_room
{
	int				id;
	char			*name;
	int				ant_id;
	int				yx[2];
	int				links_nb;
	int				*links;
	int				weight;
	struct s_room	*next;
	struct s_room	*prev;
}					t_room;

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


typedef	struct		s_lem_in
{
	int				room_nb;
	long			ants;
	int				max_paths;
	int				moves;
	int				**links;
	t_room			**id_table;
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	char			*min_moves;
}					t_lem_in;

void				read_input(t_lem_in *lem);
void				algo(t_lem_in *lem);
void				error_msg(char *str);
int					only_num(char *str);
void				print_table(t_lem_in *lem);
void				print_map(t_lem_in *lem);
t_room				*find_room(t_lem_in *lem, char *name);
char				*ft_strndup(const char *s1, ssize_t len);
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
