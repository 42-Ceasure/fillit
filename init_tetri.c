/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tetri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:59:01 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 16:59:01 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		align_tetri_up(t_tetri *current)
{
	t_pos	up;

	up.x = 0;
	up.y = -current->pos[0].y;
	tetri_translate(current, up);
}

void		align_tetri_left(t_tetri *current)
{
	int		mem;
	int		i;
	t_pos	left;

	left.y = 0;
	mem = current->pos[0].x;
	i = 1;
	while (i < 4)
	{
		if (mem > current->pos[i].x)
			mem = current->pos[i].x;
		i++;
	}
	left.x = -mem;
	tetri_translate(current, left);
}

void		mesure_tetri(t_tetri *current)
{
	int		i;
	int		mem_x;
	int		mem_y;

	i = 0;
	current->origin.x = 0;
	current->origin.y = 0;
	mem_x = current->pos[0].x;
	mem_y = current->pos[0].y;
	while (i < 4)
	{
		if (mem_x < current->pos[i].x)
			mem_x = current->pos[i].x;
		if (mem_y < current->pos[i].y)
			mem_y = current->pos[i].y;
		i++;
	}
	current->w = mem_x + 1;
	current->h = mem_y + 1;
}

void		prepare_tetri(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->n_tetri)
	{
		align_tetri_up(env->tetri[i]);
		align_tetri_left(env->tetri[i]);
		mesure_tetri(env->tetri[i]);
		i++;
	}
	return ;
}
