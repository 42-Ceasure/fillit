/* BIG42HEADER */

#include "fillit.h"

int				solve(t_canvas canvas, size_t n_tetri)
{
	int			x;
	int			y;

	y = -1;
	if (canvas.offset == (int)n_tetri)
		return (1);
	while (++y <= ((int)canvas.bufsize - canvas.tetriminos[canvas.offset]->h))
	{
		x = -1;
		while (++x < (int)canvas.bufsize)
		{
			if (canvas_try_brush(&canvas) == 0)
			{
				if (solve(canvas, n_tetri))
					return (1);
				else
					canvas_undo(&canvas);
			}
			set_move(canvas.tetriminos[canvas.offset], 1, 0);
		}
		set_move(canvas.tetriminos[canvas.offset], -x, 1);
	}
	set_move(canvas.tetriminos[canvas.offset], 0, -y);
	return (0);
}

void			start_solve(t_canvas *canvas, size_t n_tetri)
{
	while (!solve(*canvas, n_tetri))
	{
		canvas->bufsize += 1;
		canvas->buffer = canvas_resize_buffer(canvas->buffer, canvas->bufsize);
	}
}

void			start_work(t_env *env)
{
	t_canvas	canvas;

	canvas.bufsize = 2;
	canvas.buffer = canvas_create_buffer(canvas.bufsize);
	canvas.offset = 0;
	prepare_tetri(env);
	canvas.tetriminos = env->tetriminos;
	start_solve(&canvas, env->n_tetri);
	print_canvas(canvas);
	return ;
}

int				process_input(char **argv, t_env *env)
{
	int 		result;

	result = open(argv[1], O_RDONLY);
	if (result == -1)
		return (-1);
	env->fd = result;
	result = get_tetriminos(env);
	return (0);
}

int				main(int ac, char **av)
{
	t_env		env;

	if (ac == 2)
	{
		if (process_input(av, &env) != 0)
			ft_putstr("error\n");
		else
			start_work(&env);
	}
	else
		ft_putstr("to use : ./fillit <file>");
	return (0);
}
