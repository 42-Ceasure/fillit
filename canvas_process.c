/* BIG42HEADER */

#include "fillit.h"

int			canvas_buf_try_pos(char **buffer, t_pos pos, size_t size)
{
	if ((pos.x >= (int)size || pos.y >= (int)size) || (buffer[pos.y][pos.x] != '.'))
			return (1);
	return (0);
}

int			canvas_try_brush(t_canvas *self)
{
	if (canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[0], self->bufsize)
		|| canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[1], self->bufsize)
		|| canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[2], self->bufsize)
		|| canvas_buf_try_pos(self->buffer, self->tetriminos[self->offset]->positions[3], self->bufsize))
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
