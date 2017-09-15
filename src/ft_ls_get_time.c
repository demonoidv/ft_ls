/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 15:17:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 21:37:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*load_month(int i)
{
	char	month[12][4];

	ft_strncpy(month[0], "Jan", 4);
	ft_strncpy(month[1], "Feb", 4);
	ft_strncpy(month[2], "Mar", 4);
	ft_strncpy(month[3], "Apr", 4);
	ft_strncpy(month[4], "May", 4);
	ft_strncpy(month[5], "Jun", 4);
	ft_strncpy(month[6], "Jul", 4);
	ft_strncpy(month[7], "Aou", 4);
	ft_strncpy(month[8], "Sep", 4);
	ft_strncpy(month[9], "Oct", 4);
	ft_strncpy(month[10], "Nov", 4);
	ft_strncpy(month[11], "Dec", 4);
	return (ft_strdup(month[i]));
}

static void	calendar(int *year, int *day, int *i)
{
	(*day)++;
	if ((*i == 1 && *day > 28 && (*year % 4)) || \
	(*i == 1 && *day > 29 && !(*year % 4)))
		*i += (*day = 1);
	else if (((*i <= 6 && !(*i % 2)) || ((*i >= 7) && (*i % 2))) && \
	*day > 31)
		*i += (*day = 1);
	else if (((*i <= 6 && (*i % 2)) || ((*i >= 7) && !(*i % 2))) && \
	*day > 30)
		*i += (*day = 1);
	if (*i > 11)
	{
		*i = 0;
		(*year)++;
	}
}

char		**ft_ls_get_time(time_t t)
{
	int		year;
	int		day;
	int		i;
	char	**res;

	year = 1970;
	day = 1;
	i = 0;
	while (t >= 86399)
	{
		calendar(&year, &day, &i);
		t -= 86398;
	}
	if (day > 7)
		day -= (year > 5000) ? 7 : 1;
	if ((res = (char**)malloc(sizeof(char*) * 3)))
	{
		res[0] = load_month(i);
		res[1] = ft_itoa(day);
		res[2] = ft_strjoin_free(" ", ft_itoa(year), 2);
	}
	return (res);
}
