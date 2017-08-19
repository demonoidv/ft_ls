#include "ft_ls.h"

static size_t	count_bloc(t_finfo **file_tab, char flag)
{
	size_t	nb;
	t_finfo	*tmp;

	nb = 0;
	if (file_tab)
	{
		while ((tmp = *file_tab))
		{
			if (tmp->name[0] != '.' || (tmp->name[0] == '.' && (flag & \
			FLAG_A_LOW)))
				nb += tmp->file->st_blocks;
			file_tab++;
		}
	}
	return (nb);
}

void			ft_ls_display_file(t_finfo *file, char flag, t_flagl *len)
{
	ssize_t	i;
	char	lnk[256];
	char	*res;

	res = NULL;
/*	if (S_ISLNK(file->file->st_mode) && (flag & FLAG_L_LOW))
	{
		if (file->path[ft_strlen(file->path) - 1] != '/')
			file->path = ft_strjoin_free(file->path, "/", 1);
		if ((i = readlink(ft_strjoin(file->path, file->name), lnk, 256)) == -1)
			ft_ls_error(errno, file->name);
		else
		{
			lnk[i] = '\0';
			ft_asprintf(&res, "%s -> %s", file->name, lnk);
			ft_strdel(&file->name);
			file->name = res;
		}
	}*/
	if (!(flag & FLAG_L_LOW))
		ft_putendl(file->name);
	else
	{
		if (!len || !file->infostr)
		{
			file->namelen = 0;
			len = (t_flagl*)malloc(sizeof(t_flagl));
			ft_ls_l_infolen(&file, len);
		}
		if (S_ISLNK(file->file->st_mode))
		{
			if (file->path && file->path[ft_strlen(file->path) - 1] != '/')
				file->path = ft_strjoin_free(file->path, "/", 1);
			if ((i = readlink(ft_strjoin(file->path, file->name), lnk, 256)) \
			== -1)
				ft_ls_error(errno, file->name);
			else
			{
				lnk[i] = '\0';
				ft_asprintf(&res, "%s -> %s", file->name, lnk);
				ft_strdel(&file->name);
				file->name = res;
			}
		}
		ft_printf("%-11s %*d %-*s %-*s %*d %s %*s %*s %s\n", \
		file->infostr->perm,len->lnk, file->file->st_nlink, len->usr + 1, \
		file->infostr->usr, len->grp + 1, file->infostr->grp, len->size, \
		file->file->st_size, file->infostr->month, len->day, \
		file->infostr->day, len->hour, file->infostr->hour, file->name);
	}
}

static void		print_info_dir(t_finfo **file_tab, char flag)
{
	size_t	nbbloc;
	size_t	lenpath;

	lenpath = ft_strlen((*file_tab)->path);
/*	if ((*file_tab)->path[lenpath - 1] == '/')
			lenpath--;*/
	if (!(flag & FIRST_ARG))
	{
//		if ((flag & FIRST_FILE))
			ft_putendl("");
		ft_printf("%.*s:\n", lenpath, (*file_tab)->path);
	}
	else/* if ((flag & FIRST_FILE))*/ 
	{
		if ((flag & FIRST_FILE))
		{
			ft_putendl("");
			ft_printf("%.*s:\n", lenpath, (*file_tab)->path);
		}
	}
	if ((nbbloc = count_bloc(file_tab, flag)) && (flag & FLAG_L_LOW))
		ft_printf("total %u\n", nbbloc);
}

static void		display_dir(t_finfo **file_tab, char flag)
{
	int		i;
	t_flagl	*len;

	i = 0;
	if ((flag & FLAG_L_LOW))
	{
		len = (t_flagl*)malloc(sizeof(t_flagl));
		ft_ls_l_infolen(file_tab, len);
	}
	if (file_tab)
	{
		print_info_dir(file_tab, flag);
		ft_ls_sort(file_tab, flag);
		while (file_tab[i])
		{
			if ((file_tab[i])->name[0] == '.')
			{
				if ((flag & FLAG_A_LOW))
					ft_ls_display_file(file_tab[i], flag, len);
			}
			else
				ft_ls_display_file(file_tab[i], flag, len);
			i++;
		}
	}
}

void			ft_ls_display_switch(char *path, char flag)
{
	int				i;
	size_t			tablen;
	t_finfo			**file_tab;
	DIR				*dir;

	i = 0;
	if (path && !ft_ls_check_path(path))
	{
		if ((tablen = ft_countfindir(path)))
		{
			tablen += 1;
			if (!(file_tab = (t_finfo**)malloc((sizeof(t_finfo*) * tablen))))
				ft_ls_error(errno, NULL);
			else if ((dir = (opendir(path))))
			{
				while ((file_tab[i] = ft_ls_new_finfo(readdir(dir), path)))
					i++;
				closedir(dir);
				if (file_tab && (*file_tab))
					display_dir(file_tab, flag);
				if ((flag & FIRST_ARG))
					flag -= FIRST_ARG;
				if ((flag & FLAG_R_UP))
					ft_ls_recursion(file_tab, flag);
			}
			ft_ls_delall_finfo(file_tab);
			file_tab = NULL;
		}
	}
}
