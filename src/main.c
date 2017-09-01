/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 02:20:02 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/01 19:42:01 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>
#include <sys/stat.h>

static t_dir	*tab_file_to_dir(t_file **tab, int flag)
{
	int		i;
	t_dir	*dir;
	t_file	**file;

	i = 0;
	dir = NULL;
	if (tab)
	{
		while (tab[i] && !S_ISDIR((tab[i])->mode))
			i++;
		if (i && (dir = (t_dir*)malloc(sizeof(t_dir))))
		{
			if ((file = (t_file**)malloc(sizeof(t_file*) * (i + 1))))
			{
				i = 0;
				while (tab[i] && !S_ISDIR((tab[i])->mode))
				{
					file[i] = tab[i];
					i++;
				}
				file[i] = NULL;
			}
			dir = ft_ls_get_dir(flag, (tab[i])->name, file);
		}
	}
	return (dir);
}

static int		display_arg(t_file **tab, int flag)
{
	int		i;
	int		perm_den;
	t_dir	*dir;

	i = 0;
	while (tab[i] && !S_ISDIR((tab[i])->mode))
		i++;
	dir = tab_file_to_dir(tab, flag);
	if (dir)
	{
		dir->flag = (dir->flag | 160);
		ft_ls_display_switch(dir);
	}
	while (tab[i])
	{
		dir = ft_ls_get_dir(flag, ft_strdup((tab[i])->name), NULL);
		if (dir->perm_den)
			perm_den = dir->perm_den;
		if (dir && i == 0 && !tab[i + 1])
			dir->flag = (dir->flag | 32);
		if (dir && i == 0)
			dir->flag = (dir->flag | 64);
		ft_ls_display_switch(dir);
		ft_ls_del_file(&(tab[i]));
		i++;
	}
	if (tab)
		free(tab);
	return (perm_den);
}

int				main(int ac, char **av)
{
	int		i;
	int		pos;
	int		flag;
	t_dir	*dir;
	t_file	**tab;

	flag = 0;
	i = 0;
	if ((pos = ft_ls_parser(ac, av, &flag)) < ac)
	{
		if ((tab = (t_file**)malloc(sizeof(t_file*) * ((ac - pos) + 1))))
		{
			tab[ac - pos] = NULL;
			while (pos < ac)
			{
				if ((tab[i] = ft_ls_get_file((flag | 32), ft_strdup(av[pos]))))
					i++;
				pos++;
			}
			if (i > 1)
				ft_ls_sort_arg(tab);
			return (display_arg(tab, flag));
		}
		return (1);
	}
	dir = ft_ls_get_dir(flag, ft_strdup("."), NULL);
	dir->flag = (flag | 32);
	ft_ls_display_switch(dir);
	return (0);
}
