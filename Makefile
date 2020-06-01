NAME = lem-in
SRCS = ./read_input.c\
	./bfs_algo.c\
	./trim.c\
	./align.c\
	./in_and_out.c\
	./input_trim.c\
	./output_trim.c\
	./last_path_check.c\
	./final_paths.c\
	./create_routes.c\
	./ants.c\
	./free_lists.c\
	./error.c\
	./print.c
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
