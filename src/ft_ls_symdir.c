/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_symdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 02:05:53 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 15:37:29 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_symdir(t_file **file, int *error, int flag)
{
	struct stat	st;
	char		lnk[1000];
	int			i;
	int			ret;

	(*file)->sympath = NULL;
	if ((*file)->perm_den)
	{
		ft_ls_error((*file)->perm_den, (*file)->name);
		ft_ls_del_file(file);
		(*error)++;
		return (0);
	}
	if (S_ISLNK((*file)->mode) && !FLAG_L_LOW(flag) && !FLAG_D_LOW(flag))
	{
		i = readlink((*file)->name, lnk, 255);
		lnk[i] = '\0';
		if (!(ret = stat((*file)->name, &st)))
		{
			if (!S_ISDIR(st.st_mode))
				return (1);
			(*file)->mode = st.st_mode;
			(*file)->sympath = ft_strdup(lnk);
		}
		else if (ret && errno != ENOENT)
			(*file)->perm_den = errno;
		if (errno == ENOENT)
			return (1);
		return (ft_ls_symdir(file, error, flag));
	}
	return (1);
}
