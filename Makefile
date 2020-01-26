# BIG42HEADER #

.PHONY:		all, clean, fclean, re
.SUFFIXES:

CC		=	gcc

CFLAG	=	-Wall -Wextra -Werror -g -O2 -std=c99 -fsanitize=address

NAME	=	fillit

SRC		=	main.c canvas_meta.c canvas_process.c parser.c tetrimino.c

OBJ		=	$(SRC:.c=.o)

all: 		_libft $(NAME)

asm:
	$(CC) -std=c99 -S -O2 $(SRC)

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