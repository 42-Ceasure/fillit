/* BIG42HEADER */

#include "fillit.h"

int			canvas_buf_try_pos(char **buf, t_pos pos, size_t size)
{
	if ((pos.x >= (int)size || pos.y >= (int)size)
		|| (buf[pos.y][pos.x] != '.'))
			return (1);
	return (0);
}

int			canvas_try_brush(t_canvas *s)
{
	if (canvas_buf_try_pos(s->buf, s->tetri[s->offset]->pos[0], s->bufsize)
		|| canvas_buf_try_pos(s->buf, s->tetri[s->offset]->pos[1], s->bufsize)
		|| canvas_buf_try_pos(s->buf, s->tetri[s->offset]->pos[2], s->bufsize)
		|| canvas_buf_try_pos(s->buf, s->tetri[s->offset]->pos[3], s->bufsize))
		return (1);
	canvas_brush(s);
	return (0);
}

void		canvas_brush(t_canvas *self)
{
	int			idx;
	t_pos		pos;

	idx = 0;
	while (idx < 4)
	{
		pos = self->tetri[self->offset]->pos[idx];
		self->buf[pos.y][pos.x] = 'A' + self->tetri[self->offset]->id;
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
		pos = self->tetri[self->offset]->pos[idx];
		self->buf[pos.y][pos.x] = '.';
		idx += 1;
	}
}
