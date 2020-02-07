# BIG42HEADER #
CC		=	gcc

CFLAG	=	-Wall -Wextra -Werror

NAME	=	fillit

LIBFT_A =	libft/libft.a

SRC		=	main.c canvas_meta.c canvas_process.c parser.c parser_next.c \
			tetrimino.c init_tetri.c solver.c

OBJ		=	$(SRC:.c=.o)

.PHONY:		all, clean, fclean, re, _libft

all: 		$(NAME)

$(NAME):	$(OBJ) $(LIBFT_A)
			$(CC) $(CFLAG) -o $@ $(OBJ) -L libft/ -lft

%.o:		%.c
			$(CC) $(CFLAG) -c -o $@ $<

$(LIBFT_A):
			make -C libft	

clean:
			make -C libft clean
			rm -f $(OBJ)

fclean: 	clean
			make -C libft fclean
			rm -f $(NAME)

re:			fclean all
