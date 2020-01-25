/* BIG42HEADER */

#include "fillit.h"

void			set_move(t_tetri *current, int x, int y)
{
	t_pos		move;

	move.x = x;
	move.y = y;
	tetri_translate(current, move);
}

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
	// printf("tetri:%d\norigin.x:%d\norigin.y:%d\nw:%d\nh:%d\n\n",
	// 	current->id, current->origin.x, current->origin.y, current->w, current->h);
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
