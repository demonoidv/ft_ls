/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:40:06 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/21 02:27:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_flag(char *arg, int *flag)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'R')
			*flag = (2 | *flag);
		else if (arg[i] == 'a')
			*flag = (4 | *flag);
		else if (arg[i] == 'l')
			*flag = (1 | *flag);
		else if (arg[i] == 'r')
			*flag = (8 | *flag);
		else if (arg[i] == 't')
			*flag = (16 | *flag);
		else if (arg[i] == '1')
			*flag += 0;
		else
			return (arg[i]);
		i++;
	}
	return (0);
}

int			ft_ls_parser(int ac, char **av, int *flag)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	while (i < ac && av[i][0] == '-' && !(res = get_flag(av[i], flag)))
		i++;
	if (res)
	{
		ft_ls_error(INVALID_FLAG, &av[i][res]);
		exit(1);
	}
	return (i);
}
