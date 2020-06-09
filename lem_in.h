/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 07:22:37 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 10:00:19 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# include "./mlx/mlx.h"

# define WIDTH 1200
# define HEIGHT 1200

typedef enum
{
	START,
	MIDDLE,
	END,
	COMMENT
}	t_type;

typedef struct		s_room
{
	char			*name;
	t_type			type;
	int				yx[2];
	int				paths[2];
	int				ants_in;
	int				bfs_val;
	struct s_room	*next;
}					t_room;

typedef	struct		s_link
{
	t_room			*start;
	t_room			*end;
	int				used;
	int				is_ant;
	struct s_link	*next;
	struct s_link	*prev;
}					t_link;

typedef struct		s_route
{
	t_link			*strt;
	int				len;
	int				is_ant;
	struct s_route	*next;
}					t_route;

typedef	struct		s_lem_in
{
	int				max_bfs;
	char			*org_input;
	long			ants;
	int				max_rout;
	int				ant_name;
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	t_link			*links;
	t_route			*routes;
	char			*pic;
	char			*line_img;
	void			*mlx;
	void			*win;
	void			*img;
	int				endian;
	int				bits_per_pixel;
	int				size_line;
	int				max;
	int				rgb;
	int				enable_visuals;
	int				move;
}					t_lem_in;

typedef struct		s_bfs
{
	t_room			*room;
	struct s_bfs	*next;
}					t_bfs;

int					draw(t_lem_in *lem, int x);
void				draw_map(t_lem_in *lem, int x);
void				draw_links(t_lem_in *lem, int x);
void				background(t_lem_in *lem);
void				line(t_lem_in *lem, int *s, int *e);

int					read_input(t_lem_in *lem);

void				trim_bfs(t_lem_in *lem);
void				trim_forks(t_lem_in *lem);
void				delet(t_lem_in *lem, t_link *link);

void				bfs_value(t_lem_in *lem);
void				align(t_lem_in *lem);
void				in_and_out(t_lem_in *lem);
void				trim_input(t_lem_in *lem);
void				trim_output(t_lem_in *lem);
void				keep_optimal(t_lem_in *lem, t_link *link,
						t_room *start, t_room *end);
t_link				*find_link(t_lem_in *lem, t_room *s, t_room *e);

void				connect_room(t_lem_in *lem, t_room *room);
void				connect_link(t_lem_in *lem, t_link *link);
t_link				*link_rooms(t_room *s, t_room *e);
t_room				*new_room(char *line, t_type type, t_lem_in *lem);

void				create_routes(t_lem_in *lem);
void				clean(t_lem_in *lem);

int					last_chance(t_lem_in *lem, t_room *room);
void				un_link(t_link *link);
int					how_many_paths(t_lem_in *lem);

void				ant_algo(t_lem_in *lem);
void				move_everyone(t_lem_in *lem);
void				move_from_start(t_lem_in *lem);
void				reverse(t_lem_in *lem, t_route *route);
int					ant_move_calc(t_lem_in *lem, t_route *route);

void				error_msg(char *str);
int					only_num(char *str);

void				print_map(t_lem_in *lem);
void				print_route(t_lem_in *lem, int len);
void				input_copy(t_lem_in *lem, char *line);

void				main_struct_free(t_lem_in *lem);

#endif
