/* BIG42HEADER */

#include "fillit.h"

int			canvas_buf_try_pos(char **buffer, t_pos pos)
{
	if (buffer[pos.y][pos.x] != '.')
		return (1);
	return (0);
}

int			canvas_try_brush(t_canvas *self)
{
	if (canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[0])
		|| canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[1])
		|| canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[2])
		|| canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[3]))
		return (1);
	canvas_brush(self);
	return (0);
}

void		canvas_brush(t_canvas *self)
{
	int			idx;
	t_pos		pos;

	idx = 0;
	while (idx < 4)
	{
		pos = self->tetriminos[self->offset]->positions[idx];
		self->buffer[pos.y][pos.x] = 'A' + self->tetriminos[self->offset]->id;
		idx += 1;
	}
	self->offset += 1;
	return ;
}

void canvas_undo(t_canvas *self)
{
	int			idx;
	t_pos		pos;

	self->offset -= 1;
	idx = 0;
	while (idx < 4)
	{
		pos = self->tetriminos[self->offset]->positions[idx];
		self->buffer[pos.y][pos.x] = '.';
		idx += 1;
	}
}
