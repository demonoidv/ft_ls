/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 23:27:22 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 14:58:00 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		display_name(char *name, char *src)
{
	ft_putstr(name);
	if (name != src)
		ft_strdel(&name);
}

void			ft_ls_color_inline(char *name, int mode)
{
	char	*tmp;

	tmp = name;
	display_name(tmp, name);
	return ;
	if (S_ISDIR(mode))
		tmp = ft_strjoin_free("\033[1;36m", ft_strjoin(name, "\033[0m"), 2);
	else if (((S_IXUSR & mode) || (S_IXGRP & mode) || \
	(S_IXOTH & mode)) && S_ISREG(mode))
		tmp = ft_strjoin_free("\033[31m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISLNK(mode))
		tmp = ft_strjoin_free("\033[35m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISCHR(mode))
		tmp = ft_strjoin_free("\033[34;43m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISBLK(mode))
		tmp = ft_strjoin_free("\033[34;46m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISFIFO(mode))
		tmp = ft_strjoin_free("\033[33m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISSOCK(mode))
		tmp = ft_strjoin_free("\033[32m", ft_strjoin(name, "\033[0m"), 2);
	//display_name(tmp, name);
}

void			ft_ls_color(char *name, int mode)
{
	char	*tmp;

	tmp = name;
	display_name(tmp, name);
	ft_putchar('\n');
	return ;
	if (S_ISDIR(mode))
		tmp = ft_strjoin_free("\033[1;36m", ft_strjoin(name, "\033[0m"), 2);
	else if (((S_IXUSR & mode) || (S_IXGRP & mode) || \
	(S_IXOTH & mode)) && S_ISREG(mode))
		tmp = ft_strjoin_free("\033[31m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISLNK(mode))
		tmp = ft_strjoin_free("\033[35m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISCHR(mode))
		tmp = ft_strjoin_free("\033[34;43m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISBLK(mode))
		tmp = ft_strjoin_free("\033[34;46m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISFIFO(mode))
		tmp = ft_strjoin_free("\033[33m", ft_strjoin(name, "\033[0m"), 2);
	else if (S_ISSOCK(mode))
		tmp = ft_strjoin_free("\033[32m", ft_strjoin(name, "\033[0m"), 2);
//	display_name(tmp, name);
//	ft_putchar('\n');
}
