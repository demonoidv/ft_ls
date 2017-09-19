/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 23:27:22 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/19 20:46:15 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		display_name(char *name, int todel)
{
	ft_putstr(name);
	if (todel)
		ft_strdel(&name);
}

void			ft_ls_color_inline(char *name, int mode)
{
	if (S_ISDIR(mode))
		name = ft_strjoin_free("\033[1;36m", ft_strjoin(name, "\033[0m"), 2);
	else if (((S_IXUSR & mode) || (S_IXGRP & mode) || \
	(S_IXOTH & mode)) && S_ISREG(mode))
		name = ft_strjoin_free("\033[31m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISLNK(mode))
		name = ft_strjoin_free("\033[35m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISCHR(mode))
		name = ft_strjoin_free("\033[34;43m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISBLK(mode))
		name = ft_strjoin_free("\033[34;46m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISFIFO(mode))
		name = ft_strjoin_free("\033[33m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISSOCK(mode))
		name = ft_strjoin_free("\033[32m", ft_strjoin(name, "\033[0m"), 2);
	else
	{
		display_name(name, 0);
		return ;
	}
	display_name(name, 1);
}

void			ft_ls_color(char *name, int mode)
{
	if (S_ISDIR(mode))
		name = ft_strjoin_free("\033[1;36m", ft_strjoin(name, "\033[0m"), 2);
	else if (((S_IXUSR & mode) || (S_IXGRP & mode) || \
	(S_IXOTH & mode)) && S_ISREG(mode))
		name = ft_strjoin_free("\033[31m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISLNK(mode))
		name = ft_strjoin_free("\033[35m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISCHR(mode))
		name = ft_strjoin_free("\033[34;43m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISBLK(mode))
		name = ft_strjoin_free("\033[34;46m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISFIFO(mode))
		name = ft_strjoin_free("\033[33m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISSOCK(mode))
		name = ft_strjoin_free("\033[32m", ft_strjoin(name, "\033[0m"), 2);
	else
	{
		display_name(name, 0);
		ft_putchar('\n');
		return ;
	}
	display_name(name, 1);
	ft_putchar('\n');
}
