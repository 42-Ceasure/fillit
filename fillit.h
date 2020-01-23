/* BIG42HEADER */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdio.h>

# include <fcntl.h>
# include "libft/inc/libft.h"

#define MAX_MINOS 26
#define TETRIMINO_INBUF 4 * 5
#define READSIZE MAX_MINOS * TETRIMINO_INBUF + MAX_MINOS

#define EOL "\n"
#define LINE_NL(s) s EOL
#define USAGE(s) LINE_NL(s)
#define PRINT_RESULT printf("Result <%d>\n", result)
#define print_positions(pos, cnt) for(int i = 0; i < cnt; i++){printf("%d - %d\n", pos[i].x, pos[i].y);}

#define LEFT 0
#define RIGHT 1

typedef struct	s_pos
{
    int			x;
    int			y;
}				t_pos;

typedef struct	s_tetri
{
	t_pos		positions[4];
	int         id;
	t_pos		origin;
	int			w;
	int			h;
}				t_tetri;

typedef struct	s_canvas
{
	char		**buffer;
	size_t		bufsize;
	t_tetri		**tetriminos;
	int			offset;
}				t_canvas;

typedef struct	s_env
{
    size_t		n_tetri;
    t_tetri		**tetriminos; // tetri_t (*tetriminos)[n_tetri];
    int			fd;
}				t_env;

t_tetri			*tetri_new(int id);
void			tetri_set_pos(t_tetri *self, t_pos [4]);
void 			tetri_translate(t_tetri *self, t_pos move);
// void			tetri_set_orientation(t_tetri *self, orien_t);
int				tetri_collide_one(t_tetri *self, t_pos);
int				tetri_collide_few(t_tetri *self, t_pos *pos, unsigned int to_chk);

int				get_tetriminos(t_env *env);

int				canvas_buf_try_pos(char **buffer, t_pos pos);
int				canvas_try_brush(t_canvas *self);
void			canvas_brush(t_canvas *self);
t_pos			*canvas_pop(t_canvas *self);

t_canvas		*canvas_new(int bufsize);
char			**canvas_create_buffer(int size);
char			**canvas_resize_buffer(char **canvas, int size);
void			print_canvas(t_canvas canvas);
void			clear_canvas(t_canvas canvas);

#endif
