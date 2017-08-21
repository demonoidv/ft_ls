/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:13:25 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/21 02:50:20 by vsporer          ###   ########.fr       */
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
	if (!FLAG_L_LOW(flag))
		ft_putendl(file->name);
	else
	{
		ft_printf("%-11s %*d %-*s %-*s", file->perm, len->lnk, file->nlink, \
		len->usr + 1, file->usr, len->grp + 1, file->grp);
		if (file->major)
			ft_printf("%*d, %*d", len->major, file->major, len->minor, \
			file->minor);
		else
			ft_printf("%*s", len->size, file->size);
		ft_printf("%s %*s %*s %s\n", file->month, len->day, file->day, \
		len->hour, file->hour, file->name);
	}
}

static void		print_info_dir(t_dir *dir)
{
	size_t	nbbloc;
	size_t	lenpath;

	lenpath = ft_strlen(dir->path);
	if (dir->path)
	{
		ft_putendl("");
		ft_printf("%.*s:\n", lenpath, dir->path);
	}
	if ((nbbloc = count_bloc(dir, dir->flag)) && FLAG_L_LOW(dir->flag))
		ft_printf("total %u\n", nbbloc);
}

static void		display_dir(t_dir *dir)
{
	int			i;
	t_file		**tab;
	t_infolen	len;

	i = 0;
	tab = dir->file;
	if (FLAG_L_LOW(dir->flag))
		ft_ls_get_infolen(tab, &len);
	if (tab)
	{
		print_info_dir(dir);
		while (tab[i])
		{
			if ((tab[i])->name[0] == '.')
			{
				if (FLAG_A_LOW(dir->flag))
					ft_ls_display_file(dir->flag, tab[i], &len);
			}
			else
				ft_ls_display_file(dir->flag, tab[i], &len);
			i++;
		}
	}
}

void			ft_ls_display_switch(t_dir *dir)
{
	if (dir)
	{
		ft_ls_sort(dir->file, dir->flag);
		display_dir(dir);
		if (FLAG_R_UP(dir->flag))
			ft_ls_recursion(dir);
		ft_ls_del_dir(dir);
	}
}
