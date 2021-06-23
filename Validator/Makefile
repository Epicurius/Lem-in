# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 17:54:23 by nneronin          #+#    #+#              #
#    Updated: 2021/06/23 12:48:22 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED				:= "\e[0;31m"
GREEN			:= "\e[0;32m"
YELLOW			:= "\e[0;33m"
BLUE			:= "\e[0;34m"
MAGENTA			:= "\e[0;35m"
CYAN			:= "\e[0;36m"
RESET			:= "\e[0m"

NAME = validator
SOURCE = ./error.c\
		./main.c\
		./read_input.c\
		./read_links.c\
		./read_rooms.c\
		./rb_tree.c\
		./rb_func.c\
		./free.c

DIR_S = srcs
SRCS = $(addprefix $(DIR_S)/,$(SOURCE))
OBJS = $(SRCS:.c=.o)

LIB_DIR	:= ../lib
LIBFT	:= -I $(LIB_DIR)/libft $(LIB_DIR)/libft/libft.a
LIBPF	:= -I $(LIB_DIR)/libpf $(LIB_DIR)/libpf/libpf.a
FLAGS	:= -Wall -Wextra -Werror

all: $(NAME)
	@printf $(CYAN)"[INFO]	$(NAME) ready!\n"$(RESET)

$(NAME):
	@gcc -o $(NAME) $(SRCS) $(LIBFT) $(LIBPF)
	@printf $(GREEN)"Compiling $(NAME)\n"$(RESET)

clean:
	@/bin/rm -f $(OBJS)
	@printf $(CYAN)"[INFO]	$(NAME) cleaned\n"$(RESET)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
