/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_infolen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:52:42 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 17:28:02 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	infolen_init(t_infolen *infolen)
{
	infolen->lnk = 0;
	infolen->usr = 0;
	infolen->grp = 0;
	infolen->size = 0;
	infolen->day = 0;
	infolen->hour = 0;
	infolen->major = 0;
	infolen->minor = 0;
}

static void	check_infolen(t_file **tab, t_infolen *infolen, int i)
{
	size_t	res;

	if ((res = ft_nbrlen((tab[i])->nlink)) > infolen->lnk)
		infolen->lnk = res;
	if ((res = ft_strlen((tab[i])->usr)) > infolen->usr)
		infolen->usr = res;
	if ((res = ft_strlen((tab[i])->grp)) > infolen->grp)
		infolen->grp = res;
	if ((res = ft_strlen((tab[i])->day)) > infolen->day)
		infolen->day = res;
	if ((res = ft_strlen((tab[i])->hour)) > infolen->hour)
		infolen->hour = res;
	if (((tab[i])->perm[0] == 'c' || (tab[i])->perm[0] == 'b') && \
	(res = ft_nbrlen((tab[i])->major) + 1) > infolen->major)
		infolen->major = res;
	if (((tab[i])->perm[0] == 'c' || (tab[i])->perm[0] == 'b') && \
	(res = ft_nbrlen((tab[i])->minor)) > infolen->minor)
		infolen->minor = res;
	if ((tab[i])->perm[0] != 'c' && (tab[i])->perm[0] != 'b' && \
	(res = ft_strlen((tab[i])->size)) > infolen->size)
		infolen->size = res;
}

void		ft_ls_get_infolen(t_file **tab, t_infolen *infolen, int flag)
{
	int		i;

	i = 0;
	infolen_init(infolen);
	while (tab[i])
	{
		if ((tab[i])->name[0] != '.' || ((tab[i])->name[0] == '.' && \
		FLAG_A_LOW(flag)))
		{
			check_infolen(tab, infolen, i);
			if (infolen->size > infolen->minor)
				infolen->minor = infolen->size;
			else if (infolen->size < infolen->minor)
				infolen->size = infolen->minor;
		}
		i++;
	}
	infolen->size += (infolen->major) ? (infolen->major + 2) : 0;
}
