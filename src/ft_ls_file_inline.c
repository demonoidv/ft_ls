/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_file_inline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 19:04:04 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 22:20:21 by vsporer          ###   ########.fr       */
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

static void		delete_hfile(t_file **tab)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		j = 0;
		i = 0;
		while (tab[i + 1])
		{
			if (tab[i]->name[0] == '.' && tab[i + 1]->name[0] != '.')
			{
				ft_swap_ptr((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
	while (tab[j] && tab[j]->name[0] != '.')
		j++;
}

static	size_t	get_len_max(t_file **tab, int flag)
{
	int		i;
	size_t	len;
	size_t	lenmax;

	i = 0;
	lenmax = 0;
	if (!FLAG_A_LOW(flag) && tab[0] && tab[1])
		delete_hfile(tab);
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

void			ft_ls_file_inline(t_file **tab, int flag)
{
	int		i;
	int		j;
	int		nbline;
	size_t	lenmax;

	i = 0;
	lenmax = get_len_max(tab, flag) + 1;
	nbline = get_nb_line(tab, flag);
	while (i < nbline)
	{
		j = 0;
		while ((nbline * j) + i < ft_tablen(tab, flag))
		{
			ft_ls_color_inline(tab[(nbline * j) + i]->name, \
			tab[(nbline * j) + i]->mode);
			if ((nbline * (j + 1)) + i < ft_tablen(tab, flag))
				ft_printf("%*c", lenmax - \
				ft_strlen(tab[(nbline * j) + i]->name), ' ');
			else
				ft_putchar('\n');
			j++;
		}
		i++;
	}
	ft_ls_sort(tab, flag);
}
