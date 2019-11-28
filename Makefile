
NAME = fillit
SRC = 	main.c \
		error.c \
		transform.c \
		solver.c \
		map.c \
		utility.c

OBJ = $(SRC:.c=.o)
INCLUDES = -I libft/inc/libft.h -I fillit.h
LIBS = -L libft/ -lft
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/ re
	@gcc -o $(NAME) $(OBJ) $(LIBS)
	@echo "compile done"

$(OBJ): %.o: %.c
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@ 

clean:
	@rm -f $(OBJ)
	@make -C Libft/ clean
	@echo "clean done"

fclean: clean
	@rm -f $(NAME)
	@make -C Libft/ fclean
	@echo "fclean done"

re: fclean all
