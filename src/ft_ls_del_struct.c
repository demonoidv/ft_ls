/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_del_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 00:04:24 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/21 02:46:12 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_del_file(t_file *file)
{
	if (file->name)
		ft_strdel(&(file->name));
	ft_bzero(file->perm, 11);
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
			ft_ls_del_file(tab[i]);
			i++;
		}
		if (dir->file)
			free(dir->file);
		if (dir->path)
			ft_strdel(&(dir->path));
		free(&dir);
	}
}
