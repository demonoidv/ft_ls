/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 12:43:59 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 14:56:31 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls_display_file(int flag, t_file *file, t_infolen *len)
{
/*	else if (!FLAG_L_LOW(flag))
	{
		if (file->lenmax)
			ft_printf("%-*s", file->lenmax, file->name);
		else
			ft_putendl(file->name);
	}*/
	if (FLAG_L_LOW(flag))
	{
		ft_printf("%-11s %*d %-*s %-*s", file->perm, len->lnk, file->nlink, \
		len->usr + 1, file->usr, len->grp + 1, file->grp);
		if (file->perm[0] == 'c' || file->perm[0] == 'b')
			ft_printf("%*d, %*d ", len->major + 1, file->major, \
			len->minor, file->minor);
		else
			ft_printf("%*s ", len->size + 1, file->size);
		ft_printf("%s %*s %*s ", file->month, 2, file->day, 5, file->hour);
	}
	ft_ls_color(file->name, file->mode);
}

