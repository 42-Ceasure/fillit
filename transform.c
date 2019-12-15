/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:54:07 by cglavieu          #+#    #+#             */
/*   Updated: 2019/12/15 16:54:08 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		ft_movetop(char **tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][0] != '#' && tab[i][1] != '#'
			&& tab[i][2] != '#' && tab[i][3] != '#')
		{
			while (tab[i][j])
			{
				if (tab[i][j] == '#')
				{
					tab[i][j - 5] = '#';
					tab[i][j] = '.';
				}
				j++;
			}
			j = 0;
		}
		i++;
	}
}

char			**ft_place_tetri(char **tab)
{
	int		i;
	int		j;

	ft_movetop(tab);
	i = 0;
	while (tab[i])
	{
		while (tab[i][0] != '#' && tab[i][5] != '#'
			&& tab[i][10] != '#' && tab[i][15] != '#')
		{
			j = 0;
			while (tab[i][j])
			{
				if (tab[i][j] == '#')
				{
					tab[i][j - 1] = '#';
					tab[i][j] = '.';
				}
				j++;
			}
		}
		i++;
	}
	return (tab);
}

static int		ft_creat_tetri(char **tab, char ***tab3d, int i)
{
	int		j;
	int		k;
	int		l;

	ft_nb_zero(&j, &k, &l);
	while (tab[i][j])
	{
		if (!(tab3d[i][k] = (char*)malloc(sizeof(char) * 5)))
			return (0);
		while (l < 4)
		{
			tab3d[i][k][l] = tab[i][j];
			j++;
			l++;
		}
		j++;
		l = 0;
		k++;
	}
	return (1);
}

char			***ft_split(char **tab)
{
	char	***tab3d;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	if (!(tab3d = (char***)malloc(sizeof(char**) * (ft_cntpieces(tab) + 1))))
		return (NULL);
	while (tab[i])
	{
		ft_nb_zero(&j, &k, &l);
		if (!(tab3d[i] = (char**)malloc(sizeof(char*) * 5)))
			return (NULL);
		if (ft_creat_tetri(tab, tab3d, i) == 0)
			return (NULL);
		i++;
	}
	tab3d[i] = NULL;
	return (tab3d);
}
