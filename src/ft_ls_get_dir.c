/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:23:52 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 19:46:21 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
static void	sort_error(t_file **tab)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		i = 0;
		j = 0;
		while (tab[i + 1])
		{
			if (tab[i]->perm_den && !tab[i + 1]->perm_den)
			{
				ft_swap_ptr((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}
*/
static void	create_file_tab(t_dir *dir)
{
	int				i;
	int				nbfile;
	DIR				*sdir;
	struct dirent	*file;

	i = 0;
	dir->file = NULL;
	if ((nbfile = ft_countfindir(dir->path)) && \
	(dir->file = (t_file**)malloc(sizeof(t_file*) * (nbfile + 1))))
	{
		sdir = opendir(dir->path);
		while ((file = readdir(sdir)))
		{
			if ((dir->file[i] = ft_ls_get_file(dir->flag, \
			ft_ls_get_path(dir->path, file->d_name))))
				i++;
		}
		closedir(sdir);
		dir->file[i] = NULL;
	}
}

t_dir		*ft_ls_get_dir(int flag, char *path, t_file **tab)
{
	t_dir	*dir;

	dir = (t_dir*)malloc(sizeof(t_dir));
	if (dir)
	{
		if (path)
			dir->path = ft_strdup(path);
		else
			dir->path = NULL;
		dir->perm_den = 0;
		dir->flag = flag;
		if (tab)
			dir->file = tab;
		else
			create_file_tab(dir);
		if (!dir->file)
			dir->perm_den = errno;
	}
	return (dir);
}
