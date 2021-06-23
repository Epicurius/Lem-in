# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 17:54:23 by nneronin          #+#    #+#              #
#    Updated: 2021/06/23 12:48:08 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED				:= "\e[0;31m"
GREEN			:= "\e[0;32m"
YELLOW			:= "\e[0;33m"
BLUE			:= "\e[0;34m"
MAGENTA			:= "\e[0;35m"
CYAN			:= "\e[0;36m"
RESET			:= "\e[0m"

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

all: libs validator $(NAME)
	@printf $(CYAN)"[INFO]	$(NAME) ready!\n"$(RESET)

$(NAME):
	@gcc -o $(NAME) $(SRCS) $(LIBFT) $(LIBPF)
	@printf $(GREEN)"Compiling $(NAME)\n"$(RESET)

libs: $(LIB_DIR)
	@make -C ./lib/libft
	@make -C ./lib/libpf

validator:
	@make -C ./validator

clean:
	@/bin/rm -f $(OBJS)
	@make clean -C ./lib/libft
	@make clean -C ./lib/libpf
	@make clean -C ./validator
	@printf $(CYAN)"[INFO]	$(NAME) cleaned\n"$(RESET)

fclean: clean
	@make fclean -C ./lib/libft
	@make fclean -C ./lib/libpf
	@make fclean -C ./validator
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean, libs, validator
