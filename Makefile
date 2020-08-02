NAME = lem-in
SRCS = 	./error.c\
	./main.c\
	./print.c\
	./ft_strndup.c\
	./read_input.c\
	./algo.c\
	./path_find.c\
	./help_path_func.c\
	./help_func.c\
	./save.c\
	./bfs.c\
	./dist_val.c\
	./ants.c

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
