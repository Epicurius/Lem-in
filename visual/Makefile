NAME = vis
SRCS = ./read_input.c\
	./draw.c\
	./main.c
FLAGS = -Wall -Werror -Werror
INCLUDES = ../libft/libft.a
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRCS) $(INCLUDES) -L./mlx/ -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
