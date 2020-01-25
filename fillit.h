/* BIG42HEADER */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdio.h>

# include <fcntl.h>
# include "libft/inc/libft.h"

#define MAX_MINOS 26
#define TETRIMINO_INBUF 4 * 5
#define READSIZE MAX_MINOS * TETRIMINO_INBUF + MAX_MINOS

#define LEFT 0
#define RIGHT 1

#define M_U 0, -1
#define M_D 0, 1
#define M_L	-1, 0
#define M_R	1, 0

typedef struct	s_pos
{
    int			x;
    int			y;
}				t_pos;

typedef struct	s_tetri
{
	t_pos		pos[4];
	int         id;
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
    t_tetri		**tetri; // tetri_t (*tetri)[n_tetri];
    int			fd;
}				t_env;

t_tetri			*tetri_new(int id);
void			tetri_set_pos(t_tetri *self, t_pos [4]);
void 			tetri_translate(t_tetri *self, t_pos move);
// void			tetri_set_orientation(t_tetri *self, orien_t);
int				tetri_collide_one(t_tetri *self, t_pos);
int				tetri_collide_few(t_tetri *self, t_pos *pos, unsigned int to_chk);
void			set_move(t_tetri *current, int x, int y);
void			align_tetri_up(t_tetri *current);
void			align_tetri_left(t_tetri *current);
void			prepare_tetri(t_env *env);

int				get_tetriminos(t_env *env);

int				canvas_buf_try_pos(char **buf, t_pos pos, size_t);
int				canvas_try_brush(t_canvas *self);
void			canvas_brush(t_canvas *self);
void			canvas_undo(t_canvas *self);

t_canvas		*canvas_new(int bufsize);
char			**canvas_create_buffer(int size);
char			**canvas_resize_buffer(char **canvas, int size);
void			print_canvas(t_canvas canvas);
void			clear_canvas(t_canvas canvas);

#endif
