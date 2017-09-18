/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:13:25 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 20:36:56 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	error_file(t_file **tab)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		if (tab[i]->perm_den)
		{
			j = 0;
			ft_ls_error(tab[i]->perm_den, tab[i]->path);
			ft_ls_del_file(&tab[i]);
			while (tab[j])
				j++;
			if (tab[--j])
			{
				tab[i] = tab[j];
				tab[j] = NULL;
			}
		}
		i++;
	}
}

static void		error_in_dir(t_dir *dir)
{
	int		i;
	char	*tmp;

	i = 0;
	error_file(dir->file);
	ft_ls_sort(dir->file, dir->flag);
	while (dir->file && dir->file[i] && dir->file[i]->perm_den)
	{
		if (dir->file[i]->name[0] != '.' || (dir->file[i]->name[0] == '.' \
		&& FLAG_A_LOW(dir->flag)))
			ft_ls_error(dir->file[i]->perm_den, dir->file[i]->name);
		ft_strdel(&dir->file[i]->name);
		ft_memdel((void**)&(dir->file[i]));
		i++;
	}
	if (dir->perm_den)
	{
		if (dir->path)
		{
			tmp = ft_ls_getname_inpath(dir->path);
			ft_ls_error(dir->perm_den, tmp);
			ft_strdel(&tmp);
		}
		ft_memdel((void**)&(dir->file));
	}
}

static void		print_info_dir(t_dir *dir)
{
	size_t	lenpath;

	if (dir->file && !dir->perm_den)
		dir->perm_den = dir->file[0]->perm_den;
	if (!ISARGFILE(dir->flag) && dir->path)
	{
		lenpath = ft_strlen(dir->path);
		if (!ISFIRST(dir->flag))
			ft_putendl("");
		ft_printf("%.*s:\n", lenpath, dir->path);
	}
	else if (ISARGFILE(dir->flag))
		dir->flag = (dir->flag ^ 32);
	if (FLAG_L_LOW(dir->flag) && !ISFILE(dir->flag) && !dir->perm_den && \
	ft_ls_check_hfile(dir->file, dir->flag))
		ft_printf("total %u\n", ft_ls_count_bloc(dir, dir->flag));
	else if (ISFILE(dir->flag))
		dir->flag = (dir->flag ^ 128);
	error_in_dir(dir);
}

static void		display_dir(t_dir *dir)
{
	int			i;
	t_file		**tab;
	t_infolen	len;

	i = 0;
	tab = dir->file;
	print_info_dir(dir);
	if (tab && !dir->perm_den)
	{
		if (FLAG_L_LOW(dir->flag) && !tab[0]->perm_den)
			ft_ls_get_infolen(tab, &len, dir->flag);
		else if (!tab[0]->perm_den && !FLAG_ONE(dir->flag))
		{
			ft_ls_file_inline(dir->file, dir->flag);
			return ;
		}
		while (tab[i])
		{
			if ((tab[i])->name[0] == '.' && FLAG_A_LOW(dir->flag))
				ft_ls_display_file(dir->flag, tab[i], &len);
			else if ((tab[i])->name[0] != '.')
				ft_ls_display_file(dir->flag, tab[i], &len);
			i++;
		}
	}
}

void			ft_ls_display_switch(t_dir *dir)
{
	if (dir)
	{
		if (!dir->perm_den && dir->file && !dir->file[0]->perm_den)
			ft_ls_sort(dir->file, dir->flag);
		display_dir(dir);
		if (FLAG_R_UP(dir->flag) && !dir->perm_den)
		{
			if (ISFIRST(dir->flag))
				dir->flag -= 64;
			ft_ls_recursion(dir);
		}
		ft_ls_del_dir(dir);
	}
}
