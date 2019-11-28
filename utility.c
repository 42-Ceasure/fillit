
#include "fillit.h"

int			ft_cntpiecechar(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '#')
			count++;
		i++;
	}
	return (count / 4);
}

int			ft_cntpieces(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void		ft_nb_zero(int *j, int *k, int *l)
{
	*j = 0;
	*k = 0;
	*l = 0;
}

void		hint_usage(void)
{
	ft_putstr("usage: ./fillit file\n");
	exit(EXIT_FAILURE);
}

void		ft_error(void)
{
	ft_putstr("error\n");
	exit(EXIT_FAILURE);
}
