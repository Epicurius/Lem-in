# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 17:54:23 by nneronin          #+#    #+#              #
#    Updated: 2021/06/10 16:13:47 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
SOURCE = ./error.c\
		./main.c\
		./print.c\
		./read_input.c\
		./read_links.c\
		./read_rooms.c\
		./rb_tree.c\
		./rb_func.c\
		./algo.c\
		./path_find.c\
		./path_find_utils.c\
		./negative_flow.c\
		./help_func.c\
		./save.c\
		./bfs.c\
		./dist_val.c\
		./ants.c\
		./print_ants.c\
		./free.c

DIR_S = srcs
SRCS = $(addprefix $(DIR_S)/,$(SOURCE))
OBJS = $(SRCS:.c=.o)

LIB_DIR	:= ./lib
LIBFT	:= -I $(LIB_DIR)/libft $(LIB_DIR)/libft/libft.a
LIBPF	:= -I $(LIB_DIR)/libpf $(LIB_DIR)/libpf/libpf.a
FLAGS	:= -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc -o $(NAME) $(SRCS) $(LIBFT) $(LIBPF)
	@echo "$(NAME) was successfully created."
clean:
	@/bin/rm -f $(OBJS)
	@echo "$(NAME) was cleaned."

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
