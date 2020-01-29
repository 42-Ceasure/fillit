/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:59:42 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 16:59:43 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			read_all(int fd, char **fb)
{
	int		result;
	size_t	n_tetri;
	void	*buf;

	buf = malloc(READSIZE);
	n_tetri = -1;
	if (buf == NULL)
		exit(-1);
	ft_bzero(buf, READSIZE);
	result = read(fd, buf, READSIZE);
	if (result == -1 || result == READSIZE
		|| result % (TETRIMINO_INBUF + 1) != TETRIMINO_INBUF)
	{
		free(buf);
		*fb = NULL;
		return (n_tetri);
	}
	n_tetri = (result + 1) / (TETRIMINO_INBUF + 1);
	*fb = buf;
	return (n_tetri);
}

void		*allocate_clean_space(t_env *env)
{
	void	*ptr;

	ptr = malloc(sizeof(void *) * env->n_tetri);
	if (ptr == NULL)
		exit(-1);
	ft_bzero(ptr, sizeof(void *) * env->n_tetri);
	return (ptr);
}

int			parse_raw(t_env *env, char *raw)
{
	int		result;
	size_t	cnt;
	void	*ptr;

	cnt = 0;
	ptr = allocate_clean_space(env);
	env->tetri = ptr;
	while (cnt < env->n_tetri)
	{
		ptr = tetri_new(cnt);
		result = parse_next(ptr, raw);
		if (result == -1 || (raw[TETRIMINO_INBUF] != 0
			&& raw[TETRIMINO_INBUF] != '\n'))
			break ;
		env->tetri[cnt++] = ptr;
		if (raw[TETRIMINO_INBUF] == 0 && cnt == env->n_tetri)
			return (0);
		raw = &(raw[TETRIMINO_INBUF + 1]);
	}
	free(ptr);
	while (cnt--)
		free(env->tetri[cnt]);
	free(env->tetri);
	return (-1);
}

int			get_tetriminos(t_env *env)
{
	int		result;
	char	*raw;

	result = read_all(env->fd, &raw);
	if (result == -1)
		ft_putendl("error");
	env->n_tetri = result;
	result = parse_raw(env, raw);
	if (result == -1)
		ft_putendl("error");
	return (0);
}
