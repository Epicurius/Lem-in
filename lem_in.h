#ifndef LEM_IN_H
# define LEM_IN_H

# include "./libft/libft.h"
# include "./libft/get_next_line.h"

typedef enum
{
	START,
	MIDDLE,
	END,
	COMMENT
}	t_type;

typedef struct		s_room
{
	char		*name;
	t_type		type;
	int		yx[2];
	int		paths[2];
	int		ants_in;
	int		bfs_val;
	struct s_room	*next;
}			t_room;

typedef	struct		s_link
{
	t_room		*start;
	t_room		*end;
	int		used;
	int		is_ant;
	struct s_link	*next;
	struct s_link	*prev;
}			t_link;

typedef struct		s_route
{
	t_link		*strt;
	int		len;
	int		is_ant;
	struct s_route	*next;
}			t_route;

typedef	struct		s_lem_in
{
	int 		max_bfs;
	long		ants;
	int		ants_end;
	int		max_rout;
	int		ant_name;
	t_room		*start;
	t_room		*end;
	t_room		*rooms;
	t_link		*links;
	t_route		*routes;
}			t_lem_in;

typedef struct		s_bfs
{
	t_room		*room;
	struct	s_bfs	*next;
}			t_bfs;

void	bfs_value(t_lem_in *lem);
void	trim_bfs(t_lem_in *lem);
void	trim_forks(t_lem_in *lem);
void	delet(t_lem_in *lem, t_link *link);
void	align(t_lem_in *lem);
void	in_and_out(t_lem_in *lem);
void	trim_input(t_lem_in *lem);
void	trim_output(t_lem_in *lem);
void	keep_optimal(t_lem_in *lem, t_link *link, t_room *start, t_room *end);
t_link	*find_link(t_lem_in *lem, t_room *s, t_room *e);

void	create_routes(t_lem_in *lem);
void	clean(t_lem_in *lem);

int	last_chance(t_lem_in *lem, t_room *room);
void	un_link(t_lem_in *lem, t_link *link);
int	how_many_paths(t_lem_in *lem);

void	ant_algo(t_lem_in *lem);

void	error_msg(char *str);
int	only_num(char *str);

void	print_map(t_lem_in *lem);

void	main_struct_free(t_lem_in *lem);
#endif
