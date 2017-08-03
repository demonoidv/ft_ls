#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# define FLAG_L_LOW 0b00010000
# define FLAG_R_UP 0b00001000
# define FLAG_A_LOW 0b00000100
# define FLAG_R_LOW 0b00000010
# define FLAG_T_LOW 0b00000001
# define FLAG_ALL 0b00011111
# define INVALID_FLAG 0
# define USAGE "usage: ft_ls [-Ralrt] [file ...]"

int		ft_ls_parser(int ac, char **av, char *flag);
void	ft_ls_error(int err_flag, char *str);

#endif
