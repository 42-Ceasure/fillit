/* BIG42HEADER */

#include "fillit.h"

t_tetri *tetri_new(int id)
{
	t_tetri *new;

	new = malloc(sizeof(*new));
	if (!new)
		exit(-1);
	bzero(new, sizeof(*new));
	new->id = id;
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

	res[0].x = (self->pos)[0].x + move.x;
	res[1].x = (self->pos)[1].x + move.x;
	res[2].x = (self->pos)[2].x + move.x;
	res[3].x = (self->pos)[3].x + move.x;
	res[0].y = (self->pos)[0].y + move.y;
	res[1].y = (self->pos)[1].y + move.y;
	res[2].y = (self->pos)[2].y + move.y;
	res[3].y = (self->pos)[3].y + move.y;
	tetri_set_pos(self, res);
	self->origin.x += move.x;
	self->origin.y += move.y;
	return;
}


/**
 *  @pos: array of pos to check against
 *  @to_chk: number of elements in @pos
 *  
 *  this function return the number of pos in pos which overlap with
 *  the tetri's own pos - or 0 
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
 *  return 1 if pos overlap with tetri's own pos 
 */

int tetri_collide_one(t_tetri *self, t_pos pos)
{
	if ((self->pos)[0].x == pos.x && (self->pos)[0].y == pos.y)
		return 1;
	if ((self->pos)[1].x == pos.x && (self->pos)[1].y == pos.y)
		return 1;
	if ((self->pos)[2].x == pos.x && (self->pos)[2].y == pos.y)
		return 1;
	if ((self->pos)[3].x == pos.x && (self->pos)[3].y == pos.y)
		return 1;
	return 0;
}

// Private
void tetri_set_pos(t_tetri *self, t_pos new[4])
{
	void *dst;

	dst = memmove(&(self->pos), new, sizeof(self->pos));
	if (dst != &(self->pos))
		exit(-1); //Don't know if this could happen
	return;
}

// void tetri_set_orientation(t_tetri *self, orien_t new)
// {
//     self->orientation = new;
//     return;
// }
