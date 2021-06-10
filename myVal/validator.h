/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 09:19:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/10 17:02:30 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "libft.h"
# include "libpf.h"
# include "error_msg.h"

# define START_ID			0
# define END_ID				1
# define MAX_INT			2147483647
# define LINES_REQUIRED		"#Here is the number of lines required:"
# define LINES_AQUIRED		"#Here is the number of lines aquired: "
# define RB_RED				1


typedef struct s_room
{
	char			*name;
	struct s_room	*left;
	struct s_room	*right;
	struct s_room	*parent;
	size_t			flag;
	t_list			*link;
	size_t			links_nb;
	int				id;
	int				y;
	int				x;
	int				ant;
}					t_room;

typedef struct s_lem_in
{
	t_room			**ants;
	int				ant_nb;
	int				start_nb;
	int				end_nb;
	int				room_nb;
	t_room			*end;
	t_room			*start;
	t_room			*tree;
}					t_env;

void	error_msg(const char *restrict format, ...);
int		check_ant_curr_room_links(t_env *lem, int ant, t_room *room);
void	move_ants(t_env *lem, char **arr2);
void 	read_cmd(t_env *lem);
int		main(int ac, char **av);
void	balance_black_uncle_right(t_room **node, int is_left);
void	balance_black_uncle_left(t_room **node, int is_left);
void	free_lem(t_env *lem);
void	rb_balance(t_room **node, int is_left);
int		rb_insert(t_room **root, t_room *node);
void	read_links(char *line, t_env *lem);
char	*read_rooms(char *line, t_env *lem);
void	read_ants(t_env *lem, char *line);
void	read_input(t_env *lem);
void	find_links(char *line, t_env *lem);
t_room	*new_room(t_env *lem, char *line, int id);
int		room_type(t_env *lem, char *line);
t_room	*find_room(t_room *root, char *name);

#endif
