/* BIG42HEADER */

#include "fillit.h"

int			canvas_try_put(t_canvas *self, t_pos positions[4])
{
	if (canvas_buf_try_pos(self->buffer, positions[0])
		|| canvas_buf_try_pos(self->buffer, positions[1])
		|| canvas_buf_try_pos(self->buffer, positions[2])
		|| canvas_buf_try_pos(self->buffer, positions[3]))
		return 1;
	canvas_put(self, positions);
	return 0;
}

void		canvas_put(t_canvas *self, t_pos positions[4])
{
	void		*ptr;
	int			idx;
	t_pos		pos;

	ptr = list_new();
	if (!ptr)
		return ; //error
	idx = 0;
	while(idx < 4 && (pos = positions[idx++], 1))
		self->buffer[pos.x][pos.y] = 'X';
	self->n_hist += 1;
	list_push(&self->history, ptr);
	self->history->data = positions;
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
	while (idx < 4 && (pos = *(t_pos *)((t_list *)ptr)->data, 1))
		self->buffer[pos.x][pos.y] = '.';
	return ptr;	
}

int			canvas_buf_try_pos(char **buffer, t_pos pos)
{
	if (buffer[pos.x][pos.y] != '.')
		return (1);
	return 0;
}
