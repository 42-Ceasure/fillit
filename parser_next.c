/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:09:44 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 17:09:48 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	position_set(t_pos *pos, int x, int y)
{
	pos->x = x;
	pos->y = y;
	return ;
}

int			position_from_raw(t_pos pos[4], char raw[TETRIMINO_INBUF])
{
	int		idx;
	int		pos_cnt;

	idx = 0;
	pos_cnt = 0;
	while (idx < TETRIMINO_INBUF)
	{
		if (idx % 5 == 4 && raw[idx] != '\n')
			break ;
		else if (raw[idx] == '#')
		{
			pos_cnt += 1;
			position_set(&pos[pos_cnt - 1], idx % 5, idx / 5);
		}
		else if (raw[idx] != '\n' && raw[idx] != '.')
			break ;
		idx += 1;
	}
	if (pos_cnt != 4)
		return (-1);
	return (0);
}

int			verify_tetri(t_tetri *tetri)
{
	int		result;
	int		cnt;
	int		idx;
	t_pos	pos[4];

	idx = 0;
	cnt = 0;
	result = 0;
	while (idx < 4)
	{
		position_set(&pos[0], tetri->pos[idx].x, tetri->pos[idx].y + 1);
		position_set(&pos[1], tetri->pos[idx].x, tetri->pos[idx].y - 1);
		position_set(&pos[2], tetri->pos[idx].x - 1, tetri->pos[idx].y);
		position_set(&pos[3], tetri->pos[idx].x + 1, tetri->pos[idx].y);
		result = tetri_collide_few(tetri, pos, 4);
		if (result == 0)
			return (-1);
		cnt += result;
		idx++;
	}
	return (cnt == 6 || cnt == 8) ? 0 : -1;
}

int			parse_next(t_tetri *next, char *raw_tetri)
{
	int		result;

	result = position_from_raw(next->pos, raw_tetri);
	if (result == -1)
		return (result);
	result = verify_tetri(next);
	if (result == -1)
		return (result);
	return (0);
}
