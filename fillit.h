/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:58:49 by cglavieu          #+#    #+#             */
/*   Updated: 2020/01/29 16:58:50 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdio.h>

# include <fcntl.h>
# include "libft/inc/libft.h"

# define MAX_MINOS 26
# define TETRIMINO_INBUF 20
# define READSIZE 546
# define LEFT 0
# define RIGHT 1

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_tetri
{
	t_pos		pos[4];
	int			id;
	t_pos		origin;
	int			w;
	int			h;
}				t_tetri;

typedef struct	s_canvas
{
	char		**buf;
	size_t		bufsize;
	t_tetri		**tetri;
	int			offset;
	size_t		op_count;
}				t_canvas;

typedef struct	s_env
{
	size_t		n_tetri;
	t_tetri		**tetri;
	int			fd;
}				t_env;

int				verify_tetri(t_tetri *tetri);
int				parse_next(t_tetri *next, char *raw_tetri);

t_tetri			*tetri_new(int id);
void			tetri_set_pos(t_tetri *self, t_pos new[4]);
void			tetri_translate(t_tetri *self, t_pos move);
int				tetri_collide_one(t_tetri *self, t_pos pos);
int				tetri_collide_few(t_tetri *s, t_pos *pos, unsigned int to_chk);
void			set_move(t_tetri *current, int x, int y);
void			align_tetri_up(t_tetri *current);
void			align_tetri_left(t_tetri *current);
void			prepare_tetri(t_env *env);

int				get_tetriminos(t_env *env);

int				canvas_buf_try_pos(char **buf, t_pos pos, size_t size);
int				canvas_try_brush(t_canvas *self);
void			canvas_brush(t_canvas *self);
void			canvas_undo(t_canvas *self);

t_canvas		*canvas_new(int bufsize);
char			**canvas_create_buffer(int size);
char			**canvas_resize_buffer(char **canvas, int size);
void			print_canvas(t_canvas canvas);
void			clear_canvas(t_canvas canvas);

void			start_solve(t_canvas *canvas, size_t n_tetri);

#endif
