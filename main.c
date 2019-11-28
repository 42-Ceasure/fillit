
#include "fillit.h"

static void	zero_tetri(char **tetri, int j)
{
	int		i;

	i = 0;
	while (i < j)
	{
		*tetri = NULL;
		++tetri;
		++i;
	}
}

static char	**ft_readinput(int fd)
{
	int		i;
	int		j;
	int		ret;
	char	buf[FILLIT_BUFFER + 1];
	char	**tab;

	j = 0;
	ft_bzero(buf, FILLIT_BUFFER + 1);
	if ((ret = read(fd, buf, FILLIT_BUFFER)) < 1 || ft_testerror(buf) == 0)
		ft_error();
	i = ft_cntpiecechar(buf);
	if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	zero_tetri(tab, i + 1);
	i = 0;
	while (buf[i])
	{
		tab[j] = ft_strsub(buf, j * 21, BLOC_SIZE);
		i += 21;
		j++;
	}
	return (tab);
}

int			main(int ac, char **av)
{
	int		fd;
	char	**tab;
	char	***tab3d;
	char	**map;

	if (ac != 2)
		hint_usage();
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error();
	tab = ft_readinput(fd);
	tab = ft_place_tetri(tab);
	tab3d = ft_split(tab);
	map = ft_bigsolver(tab3d, ft_cntpieces(tab));
	ft_printmap(map);
	ft_deletemap(tab);
	ft_delete3d(tab3d);
	ft_deletemap(map);
	return (0);
}
