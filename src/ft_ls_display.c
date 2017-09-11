/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:13:25 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/11 03:12:20 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	count_bloc(t_dir *dir, int flag)
{
	size_t	nb;
	t_file	**tab;
	t_file	*tmp;

	nb = 0;
	tab = dir->file;
	if (tab)
	{
		while ((tmp = *tab))
		{
			if (tmp->name[0] != '.' || (tmp->name[0] == '.' && \
			FLAG_A_LOW(flag)))
				nb += tmp->block;
			tab++;
		}
	}
	return (nb);
}

static void		ft_ls_display_file(int flag, t_file *file, t_infolen *len)
{
	if (!FLAG_L_LOW(flag) && FLAG_ONE(flag))
		ft_putendl(file->name);
	else if (!FLAG_L_LOW(flag))
	{
		if (file->lenmax)
			ft_printf("%-*s", file->lenmax, file->name);
		else
			ft_putendl(file->name);
	}
	else
	{
		ft_printf("%-11s %*d %-*s %-*s", file->perm, len->lnk, file->nlink, \
		len->usr + 1, file->usr, len->grp + 1, file->grp);
		if (file->perm[0] == 'c' || file->perm[0] == 'b')
			ft_printf("%*d, %*d ", len->major + 1, file->major, \
			len->minor, file->minor);
		else
			ft_printf("%*s ", len->size + 1, file->size);
		ft_printf("%s %*s %*s %s\n", file->month, 2, file->day, \
		5, file->hour, file->name);
	}
}

static int		check_hfile(t_file **tab, int flag)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i] && tab[i]->name[0] == '.')
			i++;
		if (tab[i] || FLAG_A_LOW(flag))
			return (1);
	}
	return (0);
}

static void		print_info_dir(t_dir *dir)
{
	size_t	lenpath;
	char	*tmp;
	int		i;

	i = 0;
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
	check_hfile(dir->file, dir->flag))
		ft_printf("total %u\n", count_bloc(dir, dir->flag));
	else if (ISFILE(dir->flag))
		dir->flag = (dir->flag ^ 128);
	while (dir->file && dir->file[i] && dir->file[i]->perm_den)
	{
		if (dir->file)
		if (dir->file[i]->name[0] != '.' || (dir->file[i]->name[0] == '.' \
		&& FLAG_A_LOW(dir->flag)))
			ft_ls_error(dir->file[i]->perm_den, dir->file[i]->name);
		ft_strdel(&dir->file[i]->name);
		ft_memdel((void**)&dir->file[i]);
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
		ft_memdel((void**)dir->file);
	}
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
			tab = (dir->file = ft_ls_file_inline(dir->file, dir->flag));
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
				dir->flag = (dir->flag ^ 64);
			ft_ls_recursion(dir);
		}
		ft_ls_del_dir(dir);
	}
}
