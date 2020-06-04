/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:18:32 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/04 08:51:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "./mlx/mlx.h"
# define WIDTH 1200
# define HEIGHT 1200
# define EMPTY 0x131313
# define PLAYER1 0x00B500
# define PLAYER2 0xFFED00
# define Y_GRAPH 75
# define X_GRAPH 90

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

typedef struct		s_lem_in
{
	int				pause;
	char			*pic;
	void			*mlx;
	void			*win;
	void			*img;
	int				endian;
	int				bits_per_pixel;
	int				size_line;
	long			ants;
	int				ants_end;
	int				max[2];
	int				rgb;
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	t_link			*links;
}					t_lem_in;

int					draw(t_lem_in *lem);
int					read_input(t_lem_in *lem);

#endif
