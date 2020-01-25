/* BIG42HEADER */

#include "fillit.h"

int				solve(t_canvas *canvas, size_t n_tetri)
{
	int			x;
	int			y;

	y = -1;
	if (canvas->offset == (int)n_tetri)
		return (1);
	while (++y <= ((int)canvas->bufsize - canvas->tetri[canvas->offset]->h))
	{
		x = -1;
		while (++x < (int)canvas->bufsize)
		{
			canvas->op_count++;
			// printf("operation:%lu\n", canvas->op_count);
			if (canvas_try_brush(canvas) == 0)
			{
				if (solve(canvas, n_tetri))
					return (1);
				else
					canvas_undo(canvas);
			}
			set_move(canvas->tetri[canvas->offset], 1, 0);
		}
		set_move(canvas->tetri[canvas->offset], -x, 1);
	}
	set_move(canvas->tetri[canvas->offset], 0, -y);
	return (0);
}

void			start_solve(t_canvas *canvas, size_t n_tetri)
{
	while (!solve(canvas, n_tetri))
	{
		canvas->bufsize += 1;
		canvas->buf = canvas_resize_buffer(canvas->buf, canvas->bufsize);
	}
}

size_t			predict_size_min(size_t n_tetri)
{
	size_t		size;
	size_t		blocs;

	size = 2;
	blocs = 4 * n_tetri;
	while (size * size < blocs)
		size++;
	return (size);
}

void			start_work(t_env *env)
{
	t_canvas	canvas;

	canvas.op_count = 1;
	canvas.bufsize = predict_size_min(env->n_tetri);
	printf("size min : %lu\n", canvas.bufsize);
	canvas.buf = canvas_create_buffer(canvas.bufsize);
	canvas.offset = 0;
	prepare_tetri(env);
	canvas.tetri = env->tetri;
	start_solve(&canvas, env->n_tetri);
	printf("canvas solved in %lu operations\n", canvas.op_count);
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
