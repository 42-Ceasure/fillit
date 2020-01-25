/* BIG42HEADER */

#include "fillit.h"

void			reset_all_tetri(t_canvas *canvas, size_t n_tetri)
{
	size_t		i;

	i = 0;
	while (i < n_tetri)
	{
		align_tetri_up(canvas->tetriminos[i]);
		align_tetri_left(canvas->tetriminos[i]);
		i++;
	}
}

void			set_move(t_tetri *current, int x, int y)
{
	t_pos		move;

	move.x = x;
	move.y = y;
	tetri_translate(current, move);
}

int				solve(t_canvas canvas, size_t n_tetri)
{
	int			x;
	int			y;

	y = 0;
	if (canvas.offset == (int)n_tetri)
		return (1);
	printf("solve called for tetri:%d,w:%d,h:%d\n", canvas.offset,	canvas.tetriminos[canvas.offset]->w, canvas.tetriminos[canvas.offset]->h);
	while (y <= ((int)canvas.bufsize - canvas.tetriminos[canvas.offset]->h))
	{
		x = 0;
		while (x < (int)canvas.bufsize)
		{
			printf("try on x:%d,y:%d\n", x, y);
			if (canvas_try_brush(&canvas) == 0)
			{
				print_canvas(canvas);
				ft_putchar('\n');
				if (solve(canvas, n_tetri))
					return (1);
				else
					canvas_undo(&canvas);
			}
			set_move(canvas.tetriminos[canvas.offset], 1, 0);
			x++;
		}
		set_move(canvas.tetriminos[canvas.offset], -x, 1);
		y++;
	}
	set_move(canvas.tetriminos[canvas.offset], 0, -y);
	return (0);
}

void			try_solve(t_canvas *canvas, size_t n_tetri)
{
	while (!solve(*canvas, n_tetri))
	{
		ft_putendl("map too small, increase");
		// reset_all_tetri(canvas, n_tetri);
		canvas->bufsize += 1;
		// canvas->offset = 0;
		canvas->buffer = canvas_resize_buffer(canvas->buffer, canvas->bufsize);
	}
}

void			ceas_official_relay(t_env *env)
{
	t_canvas	canvas;

	canvas.bufsize = 2;
	canvas.buffer = canvas_create_buffer(canvas.bufsize);
	canvas.offset = 0;
	prepare_tetri(env);
	canvas.tetriminos = env->tetriminos;
	ft_putendl("ok let's go");
	try_solve(&canvas, env->n_tetri);
	print_canvas(canvas);
	return ;
}

int				uu_legacy_launch(char **argv, t_env *env)
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
		if (uu_legacy_launch(av, &env) != 0)
			ft_putstr("error\n");
		else
			ceas_official_relay(&env);
	}
	else
		ft_putstr("to use : ./fillit <file>");
	return (0);
}
