/* BIG42HEADER */

#include "fillit.h"

/**
 *  READSIZE: equals MAX_MINOS * TETRIMINO_INBUF + MAX_MINOS
 *      We read at most 26 minos, and 1 byte is added to detect
 *      oversized input.
 *  Read and recover in one go all tetri form our file.
 *  We also perform some kind of boundary checking on the input.
 *  Return the expected number of tetri
 *  based on boundary check. Or -1 if any error.
 */

void print_error(char *error_string, char *arg)
{
	printf(error_string, arg);
	exit(-1);
}

int read_all(int fd, char **fb)
{
	int result;
	size_t n_tetri;
	void *buf;

	buf = malloc(READSIZE);
	n_tetri = -1;
	if (buf == NULL)
		exit(-1);
	bzero(buf, READSIZE);
	result = read(fd, buf, READSIZE);
	if (result == -1 || result == READSIZE || result % (TETRIMINO_INBUF + 1) != TETRIMINO_INBUF)
	{
		free(buf);
		*fb = NULL;
		return n_tetri;
	}
	n_tetri = (result + 1) / (TETRIMINO_INBUF + 1);
	*fb = buf;
	return n_tetri;
}

static void position_set(t_pos *pos, int x, int y)
{
	pos->x = x;
	pos->y = y;
	return;
}

int position_from_raw(t_pos pos[4], char raw[TETRIMINO_INBUF])
{
	int idx;
	int pos_cnt;

	idx = 0;
	pos_cnt = 0;
	while (idx < TETRIMINO_INBUF)
	{
		if (idx % 5 == 4 && raw[idx] != '\n')
			break;
		else if (raw[idx] == '#')
		{
			pos_cnt += 1;
			position_set(&pos[pos_cnt - 1], idx % 5, idx / 5);
		}
		else if (raw[idx] != '\n' && raw[idx] != '.')
			break;
		idx += 1;
	}
	if (pos_cnt != 4)
		return (-1);
	return (0);
}

int verify_tetri(t_tetri *tetri) {
	int result;
	int cnt;
	int idx;
	t_pos pos[4];

	idx = 0;
	cnt = 0;
	result = 0;
	while(idx < 4) {
		position_set(&pos[0], tetri->pos[idx].x, tetri->pos[idx].y + 1); 
		position_set(&pos[1], tetri->pos[idx].x, tetri->pos[idx].y - 1); 
		position_set(&pos[2], tetri->pos[idx].x - 1, tetri->pos[idx].y); 
		position_set(&pos[3], tetri->pos[idx].x + 1, tetri->pos[idx].y); 
		result = tetri_collide_few(tetri, pos, 4);
		if(result == 0)
		 return (-1);
		cnt += result;
		idx++;
	}
	return (cnt == 6 || cnt == 8)? 0: -1;
}

int parse_next(t_tetri *next, char *raw_tetri)
{
	int result;

	result = position_from_raw(next->pos, raw_tetri);
	if (result == -1)
		return (result);
	result = verify_tetri(next);
	if (result == -1)
		return(result);
	return (0);
}

int parse_raw(t_env *env, char *raw)
{
	int result;
	size_t cnt;
	void *ptr;

	cnt = 0;
	ptr = malloc(sizeof(void *) * env->n_tetri);
	if (ptr == NULL)
		exit(-1);
	bzero(ptr, sizeof(void *) * env->n_tetri);
	env->tetri = ptr;
	while (cnt < env->n_tetri)
	{
		ptr = tetri_new(cnt);
		result = parse_next(ptr, raw);
		if (result == -1 || (raw[TETRIMINO_INBUF] != 0 && raw[TETRIMINO_INBUF] != '\n'))
			break;
		env->tetri[cnt++] = ptr;
		if (raw[TETRIMINO_INBUF] == 0 && cnt == env->n_tetri)
			return 0;
		raw = &(raw[TETRIMINO_INBUF + 1]);
	}
	free(ptr);
	while(cnt--)
		free(env->tetri[cnt]);
	free(env->tetri);
	return (-1);
}

int get_tetriminos(t_env *env)
{
	int result;
	char *raw;

	result = read_all(env->fd, &raw);
	if (result == -1)
		ft_putendl("error");
	env->n_tetri = result;
	result = parse_raw(env, raw);
	if (result == -1)
		ft_putendl("error");
	return (0);
}
