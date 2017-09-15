/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:28:07 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 22:28:17 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		sort_base(t_file **tab)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		i = 0;
		j = 0;
		while (tab[i + 1])
		{
			if (ft_strcmp((tab[i])->name, (tab[i + 1])->name) > 0)
			{
				ft_swap_ptr((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
		i++;
		}
	}
}

static void		sort_t(t_file **tab)
{
	int		i;
	int		j;
	time_t	mtime1;
	time_t	mtime2;

	j = 1;
	while (j)
	{
		i = (j = 0);
		while (tab[i + 1])
		{
			mtime1 = (tab[i])->mtime;
			mtime2 = (tab[i + 1])->mtime;
			if (mtime1 < mtime2 || (mtime1 == mtime2 && (tab[i])->nsec < \
			(tab[i + 1])->nsec))
			{
				ft_swap_ptr((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}

static void		sort_r(t_file **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tab[j])
		j++;
	j--;
	while (i < j)
	{
		ft_swap_ptr((void**)&tab[i], (void**)&tab[j]);
		i++;
		j--;
	}
}

static void		sort_s(t_file **tab)
{
	int					i;
	int					j;
	unsigned long long	size1;
	unsigned long long	size2;

	j = 1;
	while (j)
	{
		i = (j = 0);
		while (tab[i + 1])
		{
			size1 = ft_atoull(tab[i]->size);
			size2 = ft_atoull(tab[i + 1]->size);
			if (size1 < size2)
			{
				ft_swap_ptr((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}

void			ft_ls_sort(t_file **tab,  int flag)
{
	if (tab && tab[0] && tab[1])
	{
		sort_base(tab);
		if (FLAG_S_UP(flag))
			sort_s(tab);
		else if (FLAG_T_LOW(flag))
			sort_t(tab);
		if (FLAG_R_LOW(flag))
			sort_r(tab);
	}
}
