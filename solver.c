/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:53:53 by cglavieu          #+#    #+#             */
/*   Updated: 2019/12/15 16:53:56 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	ft_placepiece(char **tab, char **map, int xy[2], int mapsize)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = xy[0];
	y = xy[1];
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '#')
			{
				if ((x + i) >= mapsize || (y + j) >= mapsize)
					return (0);
				if (map[x + i][y + j] != '.')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void	ft_validpiece(char **tab, char **map, int xy[2], char letter)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = xy[0];
	y = xy[1];
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '#')
				map[x + i][y + j] = letter;
			j++;
		}
		i++;
	}
	return ;
}

static int	ft_solver(char ***tab, char **map, int mapsize, int i)
{
	int		xy[2];

	if (tab[i] == NULL)
		return (1);
	xy[0] = 0;
	while (xy[0] < mapsize)
	{
		xy[1] = 0;
		while (xy[1] < mapsize)
		{
			if (ft_placepiece(tab[i], map, xy, mapsize) == 1)
			{
				ft_validpiece(tab[i], map, xy, i + 'A');
				if ((ft_solver(tab, map, mapsize, i + 1)) == 1)
					return (1);
				else
					ft_validpiece(tab[i], map, xy, '.');
			}
			xy[1]++;
		}
		xy[0]++;
	}
	return (0);
}

char		**ft_bigsolver(char ***tab, int nbpieces)
{
	char	**map;
	int		mapsize;

	mapsize = ft_mapmini(nbpieces);
	if (!(map = ft_initmap(mapsize)))
		return (NULL);
	while (!(ft_solver(tab, map, mapsize, 0)))
	{
		ft_deletemap(map);
		mapsize++;
		if (!(map = ft_initmap(mapsize)))
			return (NULL);
	}
	return (map);
}
