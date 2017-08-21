/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_del_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 00:04:24 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/21 15:24:47 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_del_file(t_file **todel)
{
	t_file	*file;

	file = *todel;
	if (file->name)
		ft_strdel(&(file->name));
	ft_bzero(file->perm, 10);
	if (file->usr)
		ft_strdel(&(file->usr));
	if (file->grp)
		ft_strdel(&(file->grp));
	if (file->month)
		ft_strdel(&(file->month));
	if (file->day)
		ft_strdel(&(file->day));
	if (file->hour)
		ft_strdel(&(file->hour));
	if (file->size)
		ft_strdel(&(file->size));
/*	free(todel);
	todel = NULL;*/
}

void		ft_ls_del_dir(t_dir *dir)
{
	int		i;
	t_file	**tab;

	i = 0;
	if (dir)
	{
		tab = dir->file;
		while (tab[i])
		{
			ft_ls_del_file(&(tab[i]));
			i++;
		}
		if (tab)
			free(tab);
		if (dir->path)
			ft_strdel(&(dir->path));
/*		if (dir)
			free(&dir);
		dir = NULL;*/
	}
}
