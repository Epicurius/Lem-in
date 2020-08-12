NAME = lem-in
SRCS = 	./error.c\
		./main.c\
		./print.c\
		./ft_strndup.c\
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



OBJS = $(SRCS:.c=.o)
INCLUDES = ./libft/libft.a
ERROR_MSG = ./error_msg.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRCS) $(INCLUDES)
clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
