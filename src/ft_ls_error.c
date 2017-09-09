#include "ft_ls.h"
#include <string.h>

void	ft_ls_error(int err_flag, char *str)
{
	char	*ret;

	ret = NULL;
	if (err_flag == INVALID_FLAG)
		ret = ft_strjoin_free("illegal option -- ", \
		ft_strjoin_free(ft_strsub(str, 0, 1), \
		"\nusage: ft_ls [-Ralrt1] [file ...]", 1), 2);
	else if (str)
		ret = ft_strjoin_free(str, ft_strjoin(": ", strerror(err_flag)), 2);
	ft_putstr_fd("ft_ls: ", 2);
	ft_putendl_fd(ret, 2);
	ft_strdel(&ret);
}
