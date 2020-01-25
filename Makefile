# BIG42HEADER #

.PHONY:		all, clean, fclean, re
.SUFFIXES:

CC		=	gcc

CFLAG	=	-Wall -Wextra -Werror

NAME	=	fillit

SRC		=	main.c canvas_meta.c canvas_process.c parser.c tetrimino.c \
			init_tetri.c

OBJ		=	$(SRC:.c=.o)

all: 		_libft $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAG) -o $@ $^ -L libft/ -lft

%.o:		%.c
			$(CC) $(CFLAG) -c -o $@ $<

_libft:
			make -C libft	

clean:
			make clean -C libft
			rm -f $(OBJ)

fclean: 	clean
			rm -f $(NAME)

re:			fclean all