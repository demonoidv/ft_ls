/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 02:42:55 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 17:59:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		recursion_display(char *path, char *name, int flag)
{
	if (!ft_strcmp(path, "/"))
		path = ft_strjoin(path, name);
	else if (path[ft_strlen(path) - 1] != '/')
		path = (path) ? ft_strjoin_free(ft_strjoin(path, "/"), \
		name, 1) : ft_strdup(name);
	else
		path = (path) ? ft_strjoin(path, name) : ft_strdup(name);
	ft_ls_display_switch(ft_ls_get_dir(flag, path, NULL));
	if (path)
		ft_strdel(&path);
}

void			ft_ls_recursion(t_dir *dir)
{
	int		i;
	char	*path;
	t_file	**tab;

	i = 0;
	tab = dir->file;
	while (tab[i])
	{
		path = dir->path;
		if (S_ISDIR((tab[i])->mode))
		{
			if (ft_strcmp((tab[i])->name, ".") && \
			ft_strcmp((tab[i])->name, "..") && (tab[i]->name[0] != '.' || \
			(tab[i]->name[0] == '.' && FLAG_A_LOW(dir->flag))))
				recursion_display(path, tab[i]->name, dir->flag);
		}
		ft_ls_del_file(&tab[i]);
		i++;
	}
}
