
#include "fillit.h"

int			ft_mapmini(int nbpieces)
{
	int		i;

	i = 0;
	while ((i * i) < nbpieces * 4)
		i++;
	return (i);
}

char		**ft_initmap(int size)
{
	char	**map;
	int		temp;
	int		i;
	int		j;

	i = 0;
	temp = size;
	if (!(map = (char**)malloc(sizeof(char*) * (temp + 1))))
		return (NULL);
	while (size > 0)
	{
		j = 0;
		if (!(map[i] = (char*)malloc(sizeof(char) * (temp + 1))))
			return (NULL);
		while (j < temp)
		{
			map[i][j] = '.';
			j++;
		}
		map[i][j] = '\0';
		i++;
		size--;
	}
	map[i] = NULL;
	return (map);
}

void		ft_delete3d(char ***str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			ft_strdel(&str[i][j]);
			j++;
		}
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

void		ft_deletemap(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		ft_strdel(&map[i]);
		++i;
	}
	free(map);
}

void		ft_printmap(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		ft_putstr(map[i]);
		ft_putstr("\n");
		i++;
	}
	return ;
}
