/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 02:20:02 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 20:41:27 by vsporer          ###   ########.fr       */
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
				i = -1;
				while (tab[++i] && !S_ISDIR((tab[i])->mode))
					file[i] = tab[i];
				file[i] = NULL;
			}
			dir = ft_ls_get_dir(flag, NULL, file);
		}
	}
	return (dir);
}

static void		check_arg(t_dir *dir, t_file **tab, int i, int flag)
{
	int		perm_den;

	if (tab[i]->sympath)
	{
		dir = ft_ls_get_dir(flag, ft_strdup(tab[i]->sympath), NULL);
		dir->path = ft_strdup(tab[i]->name);
	}
	else
		dir = ft_ls_get_dir(flag, ft_strdup(tab[i]->name), NULL);
	if (dir->perm_den)
		perm_den = dir->perm_den;
	if (dir && i == 0 && !tab[i + 1] && !tab[i]->err)
		dir->flag = (dir->flag | 32);
	if (dir && i == 0)
		dir->flag = (dir->flag | 64);
	ft_ls_display_switch(dir);
	ft_ls_del_file(&(tab[i]));
}

static void		display_arg(t_file **tab, int flag)
{
	int		i;
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
		check_arg(dir, tab, i, flag);
		i++;
	}
	ft_memdel((void**)&tab);
}

static void		create_file_tab(t_file **tab, char **av, int ac, int flag)
{
	int		i;
	int		err;
	int		pos;

	i = 0;
	err = 0;
	pos = 0;
	while (pos < ac)
	{
		if (!av[pos][0])
		{
			ft_ls_error(ENOENT, av[pos]);
			exit(1);
		}
		if ((tab[i] = ft_ls_get_file((flag | 32), ft_strdup(av[pos]))))
			i += ft_ls_symdir(&(tab[i]), &err, flag);
		pos++;
	}
	tab[i] = NULL;
	if (err && tab[0])
	{
		tab[0]->err = 1;
	}
}

int				main(int ac, char **av)
{
	int		pos;
	int		flag;
	t_file	**tab;

	flag = 0;
	if ((pos = ft_ls_parser(ac, av, &flag)) == ac)
		av[--pos] = ".";
	if ((tab = (t_file**)malloc(sizeof(t_file*) * ((ac - pos) + 1))))
	{
		tab[ac - pos] = NULL;
		if (pos < ac)
			create_file_tab(tab, &av[pos], (ac - pos), flag);
		if (tab[0] && tab[1])
			ft_ls_sort_arg(tab);
		display_arg(tab, flag);
	}
	return (ft_ls_return(GET_ERR));
}
