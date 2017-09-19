/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_del_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 00:04:24 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/19 19:15:19 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_del_file(t_file **todel)
{
	if (*todel)
	{
		ft_strdel(&((*todel)->name));
		ft_strdel(&((*todel)->path));
		if (!(*todel)->perm_den)
		{
			ft_strdel(&((*todel)->sympath));
			ft_bzero((*todel)->perm, 11);
			ft_strdel(&((*todel)->usr));
			ft_strdel(&((*todel)->grp));
			ft_strdel(&((*todel)->month));
			ft_strdel(&((*todel)->day));
			ft_strdel(&((*todel)->hour));
			ft_strdel(&((*todel)->size));
		}
		ft_memdel((void**)todel);
		*todel = NULL;
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
