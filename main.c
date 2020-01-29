/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:59:15 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 16:59:16 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

size_t			predict_size_min(size_t n_tetri)
{
	size_t		size;

	size = 2;
	while (size * size < 4 * n_tetri)
		size++;
	return (size);
}

void			start_work(t_env *env)
{
	t_canvas	canvas;

	canvas.op_count = 1;
	canvas.bufsize = predict_size_min(env->n_tetri);
	canvas.buf = canvas_create_buffer(canvas.bufsize);
	canvas.offset = 0;
	prepare_tetri(env);
	canvas.tetri = env->tetri;
	start_solve(&canvas, env->n_tetri);
	print_canvas(canvas);
	return ;
}

int				process_input(char **argv, t_env *env)
{
	int			result;

	result = open(argv[1], O_RDONLY);
	if (result == -1)
		return (-1);
	env->fd = result;
	result = get_tetriminos(env);
	return (0);
}

int				main(int ac, char **av)
{
	t_env		env;

	if (ac == 2)
	{
		if (process_input(av, &env) != 0)
			ft_putstr("error\n");
		else
			start_work(&env);
	}
	else
		ft_putstr("to use : ./fillit <file>");
	return (0);
}
