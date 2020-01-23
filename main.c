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

int			canvas_next_position(t_tetri *current, int gridsize) {
	t_pos	move;

	move.x = 0;
	move.y = 0;
	if (current->origin.x + current->w + 1 > gridsize) {
		if (current->origin.y + current->h + 1 > gridsize)
			return (-1);
		move.y = 1;
		move.x = - current->origin.x;
	} else
		move.x = 1;
	printf("x, y <%d, %d> h, w <%d, %d>\n", current->origin.x, current->origin.y, current->h, current->w);
	tetri_translate(current, move);
	return 0;
}

int			solve_loop(t_canvas *self, int n_tetri) {
	int result;

	result = 0;	
	if (self->offset == n_tetri)
		return 0;
	printf("offset <%c> x,y: <%d, %d> result: <%zu>\n", self->tetriminos[self->offset]->id + 'A', self->tetriminos[self->offset]->origin.x, self->tetriminos[self->offset]->origin.y, self->bufsize);
	result = canvas_try_brush(self);
	PRINT_RESULT;
	if (result) {
		if (self->offset == 0)
			return (-1);
		result = canvas_next_position(self->tetriminos[self->offset], self->bufsize);
		// PRINT_RESULT;
		if (result) {
			canvas_undo(self);
		}
		self->tetriminos[12000] = NULL;
	}
	print_canvas(*self);
	// printf("offset <%d> x,y: <%d, %d> result: <%zu>\n", self->offset, self->tetriminos[self->offset]->origin.x, self->tetriminos[self->offset]->origin.y, self->bufsize);
	// read(0, &result, 1);
	return (solve_loop(self, n_tetri));
}

int			solve(t_canvas *canvas, int n_tetri) {
	// int error;

	printf("total %d\n", n_tetri);
	while (solve_loop(canvas, n_tetri)){
		ft_putstr("fail\n");
		canvas_resize_buffer(canvas->buffer, canvas->bufsize + 1);
		return (-1);
	}
	ft_putstr("success\n");
	return (0);
}

void		ceas_official_relay(t_env *env)
{
	t_canvas canvas;

	canvas.buffer = canvas_create_buffer(5);
	canvas.offset = 0;
	canvas.bufsize = 5;
	// ft_putstr("----------------------");
	canvas.tetriminos = env->tetriminos;
	prepare_tetri(env);
	// canvas_try_brush(&canvas);
	// canvas_try_put(&canvas, env->tetriminos[2]);
	print_canvas(canvas);
	solve(&canvas, env->n_tetri);
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
