NAME = lem-in
SRCS = ./srcs/read_input.c\
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
	./srcs/free_lists.c\
	./srcs/input_copy.c\
	./srcs/error.c\
	./srcs/print.c

OBJS = $(SRCS:.c=.o)
INCLUDES = ./libft/libft.a
ERROR_MSG = ./error_msg.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc  -o $(NAME) $(SRCS) $(INCLUDES)
clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
