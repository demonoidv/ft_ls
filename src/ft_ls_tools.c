/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 15:17:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/25 13:20:57 by demodev          ###   ########.fr       */
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
			*prev = '\0';
			while (tmp != path && *(tmp - 1) != '/')
				tmp--;
			ft_ls_error(errno, tmp);
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
/*	else if (path)
	{
		i = ft_strlen(path) - 1;
		while (&(path[i]) != path && path[i - 1] != '/')
			i--;
		ft_ls_error(errno, (path + i));
	}*/
	return (0);
}

char	*ft_ls_getname_inpath(char *path)
{
	int		i;
	int		end;

	i = (ft_strlen(path) - 1);
	end = path[i] == '/' ? (i - 1) : i;
	while (i >= 0 && path[i] != '/')
		i--;
	if (path[i] == '/')
		i++;
	return (ft_strsub(path, i, ((end - i) + 1)));
}
