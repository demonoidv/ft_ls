/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_del_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 00:04:24 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 16:06:00 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_del_file(t_file **todel)
{
	t_file	*file;

	if ((file = *todel))
	{
		ft_strdel(&(file->name));
		ft_strdel(&(file->sympath));
		if (!file->perm_den)
		{
			ft_bzero(file->perm, 10);
			ft_strdel(&(file->usr));
			ft_strdel(&(file->grp));
			ft_strdel(&(file->month));
			ft_strdel(&(file->day));
			ft_strdel(&(file->hour));
			ft_strdel(&(file->size));
		}
		ft_memdel((void**)todel);
	}
}

void		ft_ls_del_dir(t_dir *dir)
{
	int		i;
	t_file	**tab;

	i = 0;
	if (dir)
	{
		tab = dir->file;
		if (tab)
			while (tab[i])
			{
				ft_ls_del_file(&(tab[i]));
				i++;
			}
		ft_memdel((void**)&tab);
		ft_strdel(&(dir->path));
		ft_memdel((void**)&dir);
	}
}
