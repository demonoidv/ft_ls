/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 23:27:22 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 01:56:07 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_color_inline(char *name, int mode)
{
	char	*tmp;
	
	if (S_ISDIR(mode))
		tmp = ft_strjoin_free("\033[1;36m", \
		ft_strjoin(name, "\033[0m"), 2);
	else if (((S_IXUSR & mode) || (S_IXGRP & mode) || \
	(S_IXOTH & mode)) && S_ISREG(mode))
		tmp = ft_strjoin_free("\033[31m", \
		ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISLNK(mode))
		tmp = ft_strjoin_free("\033[35m", \
		ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISCHR(mode))
		tmp = ft_strjoin_free("\033[34;43m", \
		ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISBLK(mode))
		tmp = ft_strjoin_free("\033[34;46m", \
		ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISFIFO(mode))
		tmp = ft_strjoin_free("\033[33m", \
		ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISSOCK(mode))
		tmp = ft_strjoin_free("\033[32m", \
		ft_strjoin(name, "\033[0m"), 2);
	else
		tmp = name;
	ft_putstr(tmp);
	if (tmp != name)
		ft_strdel(&tmp);
}

char		*ft_ls_color(char *name, int mode)
{
	if (S_ISDIR(mode))
		name = ft_strjoin_free("\033[1;36m", \
		ft_strjoin_free(name, "\033[0m", 1), 2);
	else if (((S_IXUSR & mode) || (S_IXGRP & mode) || \
	(S_IXOTH & mode)) && S_ISREG(mode))
		name = ft_strjoin_free("\033[31m", \
		ft_strjoin_free(name, "\033[0m", 1), 2);
	else if (S_ISLNK(mode))
		name = ft_strjoin_free("\033[35m", \
		ft_strjoin_free(name, "\033[0m", 1), 2);
	else if (S_ISCHR(mode))
		name = ft_strjoin_free("\033[34;43m", \
		ft_strjoin_free(name, "\033[0m", 1), 2);
	else if (S_ISBLK(mode))
		name = ft_strjoin_free("\033[34;46m", \
		ft_strjoin_free(name, "\033[0m", 1), 2);
	else if (S_ISFIFO(mode))
		name = ft_strjoin_free("\033[33m", \
		ft_strjoin_free(name, "\033[0m", 1), 2);
	else if (S_ISSOCK(mode))
		name = ft_strjoin_free("\033[32m", \
		ft_strjoin_free(name, "\033[0m", 1), 2);
	return (name);
}

