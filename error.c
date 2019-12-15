/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:52:05 by cglavieu          #+#    #+#             */
/*   Updated: 2019/12/15 16:52:16 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		ft_testerrornxt(char *str)
{
	int		i;
	int		bn;

	i = 0;
	bn = 0;
	while (str[i])
	{
		if (str[i] != '.' && str[i] != '#' && str[i] != '\n')
			return (0);
		if (str[i] == '\n')
			bn++;
		if ((str[i] == '\n' && (str[i + 1] == '\n'
			|| str[i + 1] == '\0')) || str[i + 1] == '\0')
		{
			if (bn != 4)
				return (0);
			if (str[i + 1] == '\n' && (str[i + 2] != '.' && str[i + 2] != '#'))
				return (0);
			bn = 0;
			i++;
		}
		i++;
	}
	return (1);
}

static int		ft_testerrornxxt(char *str)
{
	int		i;
	int		dot;
	int		hash;

	i = 0;
	dot = 0;
	hash = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (str[i] == '#')
			hash++;
		if ((str[i] == '\n' && (str[i + 1] == '\n'
			|| str[i + 1] == '\0')) || str[i + 1] == '\0')
		{
			if (dot != 12 || hash != 4)
				return (0);
			dot = 0;
			hash = 0;
			i++;
		}
		i++;
	}
	return (1);
}

static int		ft_testerrornxxxt(char *str)
{
	int		i;
	int		j;
	int		link;

	i = 0;
	j = 1;
	link = 0;
	while (str[i])
	{
		while (str[i])
		{
			if (str[i] == '\n' && (str[i + 1] == '\n' || str[i + 1] == '\0'))
				break ;
			if (str[i] == '#')
				link += ft_chklnk(str, i, j);
			j++;
			i++;
		}
		if (link != 6 && link != 8)
			return (0);
		link = 0;
		j = 1;
		i = i + 2;
	}
	return (1);
}

int				ft_chklnk(char *str, int i, int j)
{
	int link;

	link = 0;
	if (j > 5 && str[i - 5] == '#')
		link++;
	if (j > 1 && str[i - 1] == '#')
		link++;
	if (j < 19 && str[i + 1] == '#')
		link++;
	if (j < 15 && str[i + 5] == '#')
		link++;
	return (link);
}

int				ft_testerror(char *str)
{
	if (!ft_testerrornxt(str))
		return (0);
	if (!ft_testerrornxxt(str))
		return (0);
	if (!ft_testerrornxxxt(str))
		return (0);
	return (1);
}
