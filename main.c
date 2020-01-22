/* BIG42HEADER */

#include "fillit.h"

void		ceas_official_relay(void)
{
	return ;
}

int			uu_legacy_launch(char **argv, t_env *env)
{
	int result;

	result = open(argv[1], O_RDONLY);
	if (result == -1)
		return (-1);
	env->fd = result;
	result = get_tetriminos(env);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;

	if (ac == 2)
	{
		if (uu_legacy_launch(av, &env) != 0)
			ft_putstr("error\n");
		else
			ceas_official_relay();
	}
	else
		ft_putstr("to use : ./fillit <file>");
	return (0);
}
