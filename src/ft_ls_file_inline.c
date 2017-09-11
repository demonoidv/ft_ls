/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_file_inline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 19:04:04 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/11 03:09:40 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

static int		ft_tablen(t_file **tab, int flag)
{
	int		i;
	int		tablen;

	i = 0;
	tablen = 0;
	while (tab[i])
	{
		if (tab[i]->name[0] != '.' || (tab[i]->name[0] == '.' && \
		FLAG_A_LOW(flag)))
			tablen++;
		i++;
	}
	return(tablen);
}

static	size_t	get_len_max(t_file **tab, int flag)
{
	int		i;
	size_t	len;
	size_t	lenmax;

	i = 0;
	lenmax = 0;
	while (tab[i])
	{
		if ((len = ft_strlen(tab[i]->name)) > lenmax && (tab[i]->name[0] \
		!= '.' || (tab[i]->name[0] == '.' && FLAG_A_LOW(flag))))
			lenmax = len;
		i++;
	}
	return (lenmax);
}

static int		get_nb_line(t_file **tab, int flag)
{
	int				nbcol;
	int				nbline;
	size_t			lenmax;
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	lenmax = get_len_max(tab, flag);
	if ((nbcol = ws.ws_col / (lenmax + 1)))
	{
		nbline = ((nbline = ft_tablen(tab, flag)) % nbcol) ? \
		(nbline / nbcol) + 1 : nbline / nbcol;
		return (nbline);
	}
	return (ft_tablen(tab, flag));
}

static t_file	**delete_hfile(t_file **tab, int flag)
{
	int		i;
	int		j;
	t_file	**new;

	i = 0;
	j = 0;
	if ((new = (t_file**)malloc((sizeof(t_file*) * ft_tablen(tab, flag) + 1))))
	{
		while (tab[i])
		{
			if (tab[i]->name[0] != '.')
				new[j++] = tab[i];
			else
				ft_ls_del_file(&(tab[i]));
			i++;
		}
		ft_memdel((void**)&tab);
		new[j] = NULL;
		return (new);
	}
	return (tab);
}

t_file			**ft_ls_file_inline(t_file **tab, int flag)
{
	int		i;
	int		j;
	int		nbline;
	size_t	lenmax;
	t_file	**new;

	i = 0;
	if (!FLAG_A_LOW(flag))
		tab = delete_hfile(tab, flag);
	if ((new = (t_file**)malloc((sizeof(t_file*) * ft_tablen(tab, flag) + 1))))
	{
		lenmax = get_len_max(tab, flag) + 1;
		nbline = get_nb_line(tab, flag);
		while (i < nbline)
		{
			j = 0;
			while ((nbline * j) + i < ft_tablen(tab, flag))
			{
				tab[(nbline * j) + i]->lenmax = lenmax;
				*new = tab[(nbline * j) + i];
				new++;
				j++;
			}
			i++;
			(*(new - 1))->lenmax = 0;
		}
		*new = NULL;
		new -= ft_tablen(tab, flag);
		ft_memdel((void**)&tab);
		return (new);
	}
	return (tab);
}
