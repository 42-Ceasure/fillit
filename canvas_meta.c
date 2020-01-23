/* BIG42HEADER */

#include "fillit.h"

char		**canvas_create_buffer(int size)
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

char		**canvas_resize_buffer(char **canvas, int size)
{
	ft_memreg(canvas);
	canvas = canvas_create_buffer(size);
	if (canvas == NULL)
		return (NULL);
	return (canvas);
}

void		print_canvas(t_canvas canvas)
{
	int			i;

	i = 0;
	while (canvas.buffer[i] != NULL)
	{
		ft_putendl(canvas.buffer[i]);
		i++;
	}
}

void		clear_canvas(t_canvas canvas)
{
	int			i;
	int			j;

	i = 0;
	while (canvas.buffer[i] != NULL)
	{
		j = 0;
		while (canvas.buffer[i][j] != '\0')
		{
			canvas.buffer[i][j] = '.';
			j++;
		}
		i++;
	}
}
