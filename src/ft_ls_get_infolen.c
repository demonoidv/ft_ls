/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_infolen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:52:42 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/21 22:15:42 by demodev          ###   ########.fr       */
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

void		ft_ls_get_infolen(t_file **tab, t_infolen *infolen)
{
	int		i;
	size_t	res;

	i = 0;
	infolen_init(infolen);
	while (tab[i])
	{
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
		if ((res = ft_nbrlen((tab[i])->major)) > infolen->major)
			infolen->major = res;
		if ((res = ft_nbrlen((tab[i])->minor)) > infolen->minor)
			infolen->minor = res;
		if ((res = (infolen->major + infolen->minor + 2)) > infolen->size)
			infolen->size = res;
		if ((res = ft_strlen((tab[i])->size)) > infolen->size)
			infolen->size = res;
		i++;
	}
}
