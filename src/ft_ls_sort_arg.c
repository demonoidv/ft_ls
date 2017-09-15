/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:21:21 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 22:25:40 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		check_and_swap(t_file **tab)
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
			if (S_ISDIR((tab[i])->mode) && \
			!S_ISDIR((tab[i + 1])->mode))
			{
				ft_swap_ptr((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}

void			ft_ls_sort_arg(t_file **tab)
{
	if (!tab[2])
	{
		if (S_ISDIR((tab[0])->mode) && \
		!S_ISDIR((tab[1])->mode))
			ft_swap_ptr((void**)&(tab[0]), (void**)&(tab[1]));
	}
	else
		check_and_swap(tab);
}
