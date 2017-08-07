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

void	ft_ls_del_finfo(t_finfo **file)
{
	t_finfo	*tmp;

	tmp = *file;
	if (tmp)
	{
		if (tmp->name)
			ft_strdel(&tmp->name);
		if (tmp->file)
			free(tmp->file);
		tmp->file = NULL;
		tmp->namelen = 0;
		tmp = NULL;
		*file = tmp;
	}
}

void	ft_ls_delall_finfo(t_finfo **file)
{
	int		i;

	i = 0;
	if (file)
	{
		while (file[i])
		{
			ft_ls_del_finfo(&(file[i]));
			i++;
		}
		free((void**)file);
	}
}

t_finfo	*ft_ls_new_finfo(struct dirent *file, char *path)
{
	char		*tmp;
	t_finfo		*info;

	if (!file || !(info = (t_finfo*)malloc(sizeof(t_finfo))))
		return (NULL);
	if ((info->name = ft_strdup(file->d_name)))
	{
		info->namelen = ft_strlen(file->d_name);
		if ((info->file = (struct stat*)malloc(sizeof(struct stat))))
		{
			if (path[ft_strlen(path) - 1] == '/')
				tmp = ft_strjoin(path, info->name);
			else
				tmp = ft_strjoin_free(ft_strjoin(path, "/"), info->name, 1);
			if (stat(tmp, info->file))
				ft_ls_error(errno, path);
			ft_strdel(&tmp);
			info->path = path;
			info->first = 0;
			return (info);
		}
		ft_strdel(&info->name);
	}
	free(file);
	return (NULL);
}
