/* BIG42HEADER */

#include "fillit.h"

t_tetri *tetri_new(void)
{
	t_tetri *new;

	new = malloc(sizeof(*new));
	if (!new)
		exit(-1);
	bzero(new, sizeof(*new));
	return (new);
}

/**
 *  Public
 */

// void tetri_rotate(t_tetri *self, int direction)
// {
//     orien_t res;

//     if (direction == LEFT)
//         res = (_CNT + self->orientation - 1) % _CNT;
//     else if (direction == RIGHT)
//         res = (_CNT + self->orientation + 1) % _CNT;
//     else
//         return;
//     tetri_set_orientation(self, res);
//     return;
// }

void tetri_translate(t_tetri *self, t_pos move)
{
	t_pos res[4];

	res[0].x = (self->positions)[0].x + move.x;
	res[1].x = (self->positions)[1].x + move.x;
	res[2].x = (self->positions)[2].x + move.x;
	res[3].x = (self->positions)[3].x + move.x;
	res[0].y = (self->positions)[0].y + move.y;
	res[1].y = (self->positions)[1].y + move.y;
	res[2].y = (self->positions)[2].y + move.y;
	res[3].y = (self->positions)[3].y + move.y;
	tetri_set_pos(self, res);
	return;
}


/**
 *  @pos: array of positions to check against
 *  @to_chk: number of elements in @pos
 *  
 *  this function return the number of positions in pos which overlap with
 *  the tetri's own positions - or 0 
 */

int tetri_collide_few(t_tetri *self, t_pos *pos, unsigned int to_chk)
{
	int idx;
	int res;

	idx = 0;
	res = 0;
	while ((unsigned int)idx < to_chk)
	{
		res += tetri_collide_one(self, pos[idx]);
		idx += 1;
	}
	return (res);
}
/**
 *  @pos: array of position to check against
 *    
 *  return 1 if pos overlap with tetri's own positions 
 */

int tetri_collide_one(t_tetri *self, t_pos pos)
{
	if ((self->positions)[0].x == pos.x && (self->positions)[0].y == pos.y)
		return 1;
	if ((self->positions)[1].x == pos.x && (self->positions)[1].y == pos.y)
		return 1;
	if ((self->positions)[2].x == pos.x && (self->positions)[2].y == pos.y)
		return 1;
	if ((self->positions)[3].x == pos.x && (self->positions)[3].y == pos.y)
		return 1;
	return 0;
}

// Private
void tetri_set_pos(t_tetri *self, t_pos new[4])
{
	void *dst;

	dst = memmove(&(self->positions), new, sizeof(*self->positions));
	if (dst != &(self->positions))
		exit(-1); //Don't know if this could happen
	return;
}

// void tetri_set_orientation(t_tetri *self, orien_t new)
// {
//     self->orientation = new;
//     return;
// }
