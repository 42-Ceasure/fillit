/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:59:59 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 16:59:59 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static inline void		set_move(t_tetri *current, int x, int y)
{
	t_pos		move;

	move.x = x;
	move.y = y;
	tetri_translate(current, move);
}

int						solve(t_canvas *canvas, size_t n_tetri)
{
	int			x;
	int			y;

	y = -1;
	if (canvas->offset == (int)n_tetri)
		return (1);
	while (++y <= ((int)canvas->bufsize - canvas->tetri[canvas->offset]->h))
	{
		x = -1;
		while (++x < (int)canvas->bufsize)
		{
			canvas->op_count++;
			if (canvas_try_brush(canvas) == 0)
			{
				if (solve(canvas, n_tetri))
					return (1);
				else
					canvas_undo(canvas);
			}
			set_move(canvas->tetri[canvas->offset], 1, 0);
		}
		set_move(canvas->tetri[canvas->offset], -x, 1);
	}
	set_move(canvas->tetri[canvas->offset], 0, -y);
	return (0);
}

void					start_solve(t_canvas *canvas, size_t n_tetri)
{
	while (!solve(canvas, n_tetri))
	{
		canvas->bufsize += 1;
		canvas->buf = canvas_resize_buffer(canvas->buf, canvas->bufsize);
	}
}
