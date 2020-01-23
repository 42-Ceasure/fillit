/* BIG42HEADER */

#include "fillit.h"

void		align_tetri_up(t_tetri *current)
{
	t_pos	up;

	up.x = 0;
	up.y = -current->positions[0].y;
	tetri_translate(current, up);
}

void		align_tetri_left(t_tetri *current)
{
	int		mem;
	int		i;
	t_pos	left;

	left.y = 0;
	mem = current->positions[0].x;
	i = 1;
	while (i < 4)
	{
		if (mem > current->positions[i].x)
			mem = current->positions[i].x;
		i++;
	}
	left.x = -mem;
	tetri_translate(current, left);
}

void		mesure_tetri(t_tetri *current)
{
	int		i;
	int 	mem_x;
	int 	mem_y;

	i = 0;
	current->origin.x = 0;
	current->origin.y = 0;
	mem_x = current->positions[0].x;
	mem_y = current->positions[0].y;
	while (i < 4)
	{
		if (mem_x < current->positions[i].x)
			mem_x = current->positions[i].x;
		if (mem_y < current->positions[i].y)
			mem_y = current->positions[i].y;
		i++;
	}
	current->w = mem_x + 1;
	current->h = mem_y + 1;
	printf("tetri:%d\norigin.x:%d\norigin.y:%d\nw:%d\nh:%d\n\n", current->id, current->origin.x, current->origin.y, current->w, current->h);
}

void		prepare_tetri(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->n_tetri)
	{
		align_tetri_up(env->tetriminos[i]);
		align_tetri_left(env->tetriminos[i]);
		mesure_tetri(env->tetriminos[i]);
		i++;
	}
	return ;
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
