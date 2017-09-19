/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 23:58:50 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/19 19:54:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>

int				ft_ls_return(int flag)
{
	static int	err;

	if (flag == SET_ERR)
		return ((err = 1));
	else if (flag == GET_ERR)
		return (err);
	else
		return (0);
}

void			ft_ls_error(int err_flag, char *str)
{
	char	*ret;

	ret = NULL;
	if (err_flag == INVALID_FLAG)
		ret = ft_strjoin_free("illegal option -- ", \
		ft_strjoin_free(ft_strsub(str, 0, 1), \
		"\nusage: ft_ls [-RSUacdlrtu1] [file ...]", 1), 2);
	else if (str)
		ret = ft_strjoin_free(str, ft_strjoin(": ", strerror(err_flag)), 2);
	ft_putstr_fd("ft_ls: ", 2);
	ft_putendl_fd(ret, 2);
	ft_ls_return(SET_ERR);
	ft_strdel(&ret);
}

static void		load_tab_with_new(t_file **dest, t_file **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = NULL;
}

void			ft_ls_error_file(t_file **tab, int flag)
{
	int		i;
	int		j;
	t_file	**new;

	i = 0;
	j = 0;
	if ((new = (t_file**)malloc(sizeof(t_file*) * \
	(ft_tablen(tab, (flag | 4)) + 1))))
	{
		while (tab[i])
		{
			if (tab[i]->perm_den)
			{
				ft_ls_error(tab[i]->perm_den, tab[i]->name);
				ft_ls_del_file(&(tab[i]));
			}
			else
				new[j++] = tab[i];
			i++;
		}
		new[j] = NULL;
		load_tab_with_new(tab, new);
		ft_memdel((void**)&new);
	}
}
