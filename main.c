/* BIG42HEADER */

#include "fillit.h"

void		align_tetri_up(t_tetri *current)
{
	int		zero;
	int		i;
	t_pos	up;

	up.x = 0;
	up.y = -1;
	zero = 0;
	i = 0;
	while (zero == 0)
	{
		i = 0;
		while (i < 4)
		{
			if (current->positions[i].y == 0)
				zero = 1;
			i++;
		}
		if (zero == 0)
			tetri_translate(current, up);
		// print_positions(current->positions, 4)
		// ft_putstr("\n");
	}
}

void		prepare_tetri(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->n_tetri)
	{
		align_tetri_up(env->tetriminos[i]);
		i++;
	}
	return ;
}

int			solve(t_canvas *canvas, int n_tetri) {
	int error;

	while (solve_loop(canvas, n_tetri)){
		resize();
	}
	//success;

}

int			canvas_next_position(t_tetri *current, int gridsize) {
	t_pos	move;

	move.x = 0;
	move.y = 0;
	if (current->origin.x + current->w >= gridsize) {
		if (current->origin.y + current->h >= gridsize)
			return (-1);
		move.y = 1;
	} else
		move.x = 1;
	tetri_translate(current, move);
}

int			solve_loop(t_canvas *self, int n_tetri) {
	int result;

	result = 0;
	if (self->offset == n_tetri)
		return 0;
	result = canvas_try_brush(self);		
	if (result == -1) {
		if (self->offset == 0)
			return (-1);
	}
	return (solve_loop(self, n_tetri));
}

void		ceas_official_relay(t_env *env)
{
	t_canvas canvas;

	canvas.buffer = canvas_create_buffer(12);
	canvas.offset = 0;
	// ft_putstr("----------------------");
	canvas.tetriminos = env->tetriminos;
	prepare_tetri(env);
	canvas_try_brush(&canvas);
	// canvas_try_put(&canvas, env->tetriminos[2]);
	print_canvas(canvas);
	return ;
}

int			uu_legacy_launch(char **argv, t_env *env)
{
	int result;

	result = open(argv[1], O_RDONLY);
	if (result == -1)
		return (-1);
	env->fd = result;
	result = get_tetriminos(env);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;

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
