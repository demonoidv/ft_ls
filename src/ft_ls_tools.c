#include "ft_ls.h"

int		ft_ls_check_path(char *path)
{
	char		*tmp;
	char		*prev;
	struct stat	st;

	tmp = path;
	prev = path;
	if (*tmp == '/')
		tmp++;
	while ((tmp = ft_strchr(tmp, '/')))
	{
		*tmp = '\0';
		if (stat(path, &st))
		{
			*prev = '\0';
			while (tmp != path && *(tmp - 1) != '/')
				tmp--;
			ft_ls_error(errno, tmp);
			return (-1);
		}
		*tmp = '/';
		prev = tmp;
		tmp++;
	}
	return (0);
}

size_t	ft_countfindir(char *path)
{
	int				i;
	DIR				*dir;
	struct dirent	*file;

	i = 0;
	if (path && (dir = opendir(path)))
	{
		while ((file = readdir(dir)))
			i++;
		closedir(dir);
		return (i);
	}
	else if (path)
	{
		i = ft_strlen(path) - 1;
		while (&(path[i]) != path && path[i - 1] != '/')
			i--;
		ft_ls_error(errno, (path + i));
	}
	return (0);
}
