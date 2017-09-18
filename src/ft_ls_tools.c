/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 15:17:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 15:10:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_check_path(char *path)
{
	char		*tmp;
	char		*prev;
	struct stat	st;

	tmp = path;
	prev = path;
	if (*tmp == '/')
		tmp++;
	while ((tmp = ft_strchr(tmp, '/')))
	{
		*tmp = '\0';
		if (stat(path, &st))
		{
			ft_ls_error(errno, path);
			return (-1);
		}
		*tmp = '/';
		prev = tmp;
		tmp++;
	}
	return (0);
}

size_t	ft_countfindir(char *path)
{
	int				i;
	DIR				*dir;

	i = 0;
	if (path && (dir = opendir(path)))
	{
		while (readdir(dir))
			i++;
		closedir(dir);
		return (i);
	}
	return (0);
}

char	*ft_ls_getname_inpath(char *path)
{
	int		i;
	int		end;

	i = (ft_strlen(path) - 1);
	end = path[i] == '/' ? (i - 1) : i;
	while (i > 0 && path[i] != '/')
		i--;
	if (path[i] == '/')
		i++;
	return (ft_strsub(path, i, ((end - i) + 1)));
}

size_t	ft_ls_count_bloc(t_dir *dir, int flag)
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

int		ft_ls_check_hfile(t_file **tab, int flag)
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
