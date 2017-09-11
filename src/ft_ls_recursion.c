/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 02:42:55 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/11 03:14:39 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_recursion(t_dir *dir)
{
	int		i;
	char	*path;
	t_file	**tab;

	i = 0;
	tab = dir->file;
	if (tab && tab[0] && tab[1])
		ft_ls_sort(tab, dir->flag);
	while (tab[i])
	{
		path = dir->path;
		if (S_ISDIR((tab[i])->mode))
		{
			if (ft_strcmp((tab[i])->name, ".") && \
			ft_strcmp((tab[i])->name, "..") && (tab[i]->name[0] != '.' || \
			(tab[i]->name[0] == '.' && FLAG_A_LOW(dir->flag))))
			{
				path = (path) ? ft_strjoin_free(ft_strjoin(path, "/"), \
				(tab[i])->name, 1) : ft_strdup((tab[i])->name);
				ft_ls_display_switch(ft_ls_get_dir(dir->flag, path, NULL));
				if (path)
					ft_strdel(&path);
			}
		}
		ft_ls_del_file(&tab[i]);
		i++;
	}
}
