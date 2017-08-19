#include "ft_ls.h"

void			ft_ls_del_finfo(t_finfo **file)
{
	t_finfo		*tmp;
	struct stat	*stat;

	tmp = *file;
	if (tmp)
	{
		if (tmp->name)
			ft_strdel(&tmp->name);
		stat = tmp->file;
		if (stat)
			free(stat);
		if (tmp->path)
			ft_strdel(&tmp->path);
		if (tmp->infostr)
		{
			ft_strdel(&tmp->infostr->usr);
			ft_strdel(&tmp->infostr->grp);
			ft_strdel(&tmp->infostr->month);
			ft_strdel(&tmp->infostr->day);
			ft_strdel(&tmp->infostr->hour);
			free(tmp->infostr);
		}
		tmp->file = NULL;
		tmp->namelen = 0;
		tmp = NULL;
		*file = tmp;
	}
}

void			ft_ls_delall_finfo(t_finfo **file)
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
		free(file);
	}
}

static t_finfo	*load_st_finfo(/*struct dirent *file, */t_finfo *info, char *path)
{
	char	*tmp;

	if (path[ft_strlen(path) - 1] == '/')
		tmp = ft_strjoin(path, info->name);
	else
		tmp = ft_strjoin_free(ft_strjoin(path, "/"), info->name, 1);
//	if ((file->d_type & DT_LNK) != DT_LNK)
/*	{
		if (stat(tmp, info->file))
			ft_ls_error(errno, path);
	}
	else*/
		if (lstat(tmp, info->file))
			ft_ls_error(errno, path);
	ft_strdel(&tmp);
	info->path = ft_strdup(path);
	return (info);
}

t_finfo			*ft_ls_new_finfo(struct dirent *file, char *path)
{
	t_finfo		*info;

	if (!file || !(info = (t_finfo*)malloc(sizeof(t_finfo))))
		return (NULL);
	if ((info->name = ft_strdup(file->d_name)))
	{
		info->namelen = ft_strlen(file->d_name);
		info->infostr = NULL;
		if ((info->file = (struct stat*)malloc(sizeof(struct stat))))
			return (load_st_finfo(/*file, */info, path));
		ft_strdel(&info->name);
	}
	free(file);
	return (NULL);
}
