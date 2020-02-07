/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:00:11 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 17:00:12 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri		*tetri_new(int id)
{
	t_tetri	*new;

	new = malloc(sizeof(*new));
	if (!new)
		exit(-1);
	ft_bzero(new, sizeof(*new));
	new->id = id;
	return (new);
}

void		tetri_translate(t_tetri *self, t_pos move)
{
	t_pos	res[4];

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
	return ;
}

int			tetri_collide_few(t_tetri *s, t_pos *pos, unsigned int to_chk)
{
	int		idx;
	int		res;

	idx = 0;
	res = 0;
	while ((unsigned int)idx < to_chk)
	{
		res += tetri_collide_one(s, pos[idx]);
		idx += 1;
	}
	return (res);
}

int			tetri_collide_one(t_tetri *self, t_pos pos)
{
	if ((self->pos)[0].x == pos.x && (self->pos)[0].y == pos.y)
		return (1);
	if ((self->pos)[1].x == pos.x && (self->pos)[1].y == pos.y)
		return (1);
	if ((self->pos)[2].x == pos.x && (self->pos)[2].y == pos.y)
		return (1);
	if ((self->pos)[3].x == pos.x && (self->pos)[3].y == pos.y)
		return (1);
	return (0);
}

void		tetri_set_pos(t_tetri *self, t_pos new[4])
{
	void	*dst;

	dst = ft_memmove(&(self->pos), new, sizeof(self->pos));
	if (dst != &(self->pos))
		exit(-1);
	return ;
}
