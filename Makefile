NAME = lem-in
SOURCE = ./error.c\
		./main.c\
		./print.c\
		./rb_func.c\
		./rb_tree.c\
		./read_input.c\
		./read_links.c\
		./read_rooms.c\
		./algo.c\
		./path_find.c\
		./help_func.c\
		./save.c\
		./bfs.c\
		./dist_val.c\
		./ants.c\
		./print_ants.c

DIR_S = srcs
SRCS = $(addprefix $(DIR_S)/,$(SOURCE))
OBJS = $(SRCS:.c=.o)
INCLUDES = ./lib/libft/libft.a
ERROR_MSG = ./error_msg.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc -o $(NAME) $(SRCS) $(INCLUDES)
	@echo "$(NAME) was successfully created."
clean:
	@/bin/rm -f $(OBJS)
	@echo "$(NAME) was cleaned."

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
