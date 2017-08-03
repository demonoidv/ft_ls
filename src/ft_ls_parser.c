#include "ft_ls.h"

static char	get_flag(char *arg, char *flag)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'R')
			*flag = (FLAG_R_UP | *flag);
		else if (arg[i] == 'a')
			*flag = (FLAG_A_LOW | *flag);
		else if (arg[i] == 'l')
			*flag = (FLAG_L_LOW | *flag);
		else if (arg[i] == 'r')
			*flag = (FLAG_R_LOW | *flag);
		else if (arg[i] == 't')
			*flag = (FLAG_T_LOW | *flag);
		else
			return (arg[i]);
		i++;
	}
	return (0);
}

int			ft_ls_parser(int ac, char **av, char *flag)
{
	int		i;
	char	res;

	i = 1;
	res = 0;
	while (i < ac && av[i][0] == '-' && !(res = get_flag(av[i], flag)))
		i++;
	if (res)
		ft_ls_error(INVALID_FLAG, &res);
	return (i);
}
