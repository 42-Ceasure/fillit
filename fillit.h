
#ifndef FILLIT_H
# define FILLIT_H

# define FILLIT_BUFFER 547
# define BLOC_SIZE 20
# define MAX_BLOC 26
# define BLOC '#'
# define VIDE '.'
# include "./libft/inc/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

void		hint_usage(void);
void		ft_error(void);
int			ft_cntpieces(char **tab);
int			ft_cntpiecechar(char *str);
int			ft_testerror(char *str);
int			ft_chklnk(char *str, int i, int j);
char		**ft_place_tetri(char **tab);
void		ft_nb_zero(int *j, int *k, int *l);
void		ft_remove_n(char ***tab);
char		***ft_split(char **tab);
char		**ft_bigsolver(char ***tab, int nbpieces);
void		ft_printmap(char **map);
int			ft_mapmini(int nbpieces);
char		**ft_initmap(int size);
void		ft_delete3d(char ***str);
void		ft_deletemap(char **map);

#endif
