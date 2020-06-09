# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 07:31:15 by nneronin          #+#    #+#              #
#    Updated: 2020/06/09 07:31:20 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
SRCS = ./srcs/read_input.c\
	   ./srcs/create_lists.c\
		./srcs/bfs_algo.c\
		./srcs/trim.c\
		./srcs/align.c\
		./srcs/in_and_out.c\
		./srcs/input_trim.c\
		./srcs/output_trim.c\
		./srcs/last_path_check.c\
		./srcs/final_paths.c\
		./srcs/create_routes.c\
		./srcs/ants.c\
		./srcs/ants2.c\
		./srcs/free_lists.c\
		./srcs/input_copy.c\
		./srcs/error.c\
		./srcs/print.c\
		./srcs/main.c\
		./srcs/standart_draw.c\
		./srcs/draw.c

OBJS = $(SRCS:.c=.o)
INCLUDES = ./libft/libft.a
ERROR_MSG = ./error_msg.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C ./libft/
	gcc -o $(NAME) $(FLAGS) $(SRCS) $(INCLUDES) -L./mlx/ -lmlx -framework OpenGL -framework AppKit
clean:
	/bin/rm -f $(OBJS)
	make -C ./libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft/ fclean

re: fclean all

.PHONY: clean, all, re, fclean
