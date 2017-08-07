#include "ft_ls.h"
#include <string.h>

void	ft_ls_error(int err_flag, char *str)
{
	char	*ret;

	ret = NULL;
	if (err_flag == INVALID_FLAG)
		ft_asprintf(&ret, "illegal option -- %c\n%s", *str, USAGE);
	else if (str)
		ft_asprintf(&ret, "%s: %s", str, strerror(err_flag));
	else
		ft_asprintf(&ret, "%s", str, strerror(err_flag));
	ft_putstr_fd("ft_ls: ", 2);
	ft_putendl_fd(ret, 2);
}
