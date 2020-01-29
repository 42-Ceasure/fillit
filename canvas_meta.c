/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_meta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:58:08 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 16:58:10 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char			**canvas_create_buffer(int size)
{
	char		**canvas;
	int			i;
	int			j;

	i = 0;
	if ((canvas = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	canvas[size] = NULL;
	while (i < size)
	{
		j = 0;
		if ((canvas[i] = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
			return (NULL);
		canvas[i][size] = '\0';
		while (j < size)
		{
			canvas[i][j] = '.';
			j++;
		}
		i++;
	}
	return (canvas);
}

char			**canvas_resize_buffer(char **canvas, int size)
{
	ft_memreg(canvas);
	canvas = canvas_create_buffer(size);
	if (canvas == NULL)
		return (NULL);
	return (canvas);
}

void			print_canvas(t_canvas canvas)
{
	int			i;

	i = 0;
	while (canvas.buf[i] != NULL)
	{
		ft_putendl(canvas.buf[i]);
		i++;
	}
}

void			clear_canvas(t_canvas canvas)
{
	int			i;
	int			j;

	i = 0;
	while (canvas.buf[i] != NULL)
	{
		j = 0;
		while (canvas.buf[i][j] != '\0')
		{
			canvas.buf[i][j] = '.';
			j++;
		}
		i++;
	}
}
