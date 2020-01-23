/* BIG42HEADER */

#include "fillit.h"

int			canvas_buf_try_pos(char **buffer, t_pos pos)
{
	if (buffer[pos.y][pos.x] != '.')
		return (1);
	return (0);
}

int			canvas_try_put(t_canvas *self, t_tetri *current)
{
	if (canvas_buf_try_pos(self->buffer, current->positions[0])
		|| canvas_buf_try_pos(self->buffer, current->positions[1])
		|| canvas_buf_try_pos(self->buffer, current->positions[2])
		|| canvas_buf_try_pos(self->buffer, current->positions[3]))
		return (1);
	canvas_put(self, current);
	return (0);
}

void		canvas_put(t_canvas *self, t_tetri *current)
{
	void		*ptr;
	int			idx;
	t_pos		pos;

	ptr = list_new();
	if (!ptr)
		return ;
	idx = 0;
	while (idx < 4)
	{
		pos = current->positions[idx++];
		self->buffer[pos.y][pos.x] = 'A' + current->id;
	}
	self->n_hist += 1;
	list_push(&self->history, ptr);
	self->history->data = current->positions;
	return ;
}

t_pos		*canvas_pop(t_canvas *self)
{
	void		*ptr;
	int			idx;
	t_pos		pos;

	ptr = list_pop(&self->history);
	self->n_hist -= 1;
	idx = 0;
	while (idx < 4)
	{
		pos = *(t_pos *)((t_list *)ptr)->data;
		self->buffer[pos.x][pos.y] = '.';
	}
	return (ptr);
}
