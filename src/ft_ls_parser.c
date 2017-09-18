/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:40:06 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 12:13:52 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_other_flag(char arg, int *flag)
{
	if (arg == '1')
		*flag = ((FLAG_L_LOW(*flag) ^ *flag) | 256);
	else if (arg == 'c')
		*flag = ((FLAG_U_UP(*flag) ^ FLAG_U_LOW(*flag) ^ *flag) | 1024);
	else if (arg == 'u')
		*flag = ((FLAG_C_LOW(*flag) ^ FLAG_U_UP(*flag) ^ *flag) | 512);
	else if (arg == 'U')
		*flag = ((FLAG_C_LOW(*flag) ^ FLAG_U_LOW(*flag) ^ *flag) | 2048);
	else if (arg == 'S')
		*flag = (*flag | 4096);
	else if (arg == 'd')
		*flag = (*flag | 8192);
	else
		return (0);
	return (1);
}

static int	get_flag(char *arg, int *flag)
{
	int		i;

	i = 1;
	if (!ft_strcmp("-", arg) && flag)
		return (-1);
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
		else if (!get_other_flag(arg[i], flag))
			return (i);
		if (FLAG_D_LOW(*flag))
			*flag = (*flag | 4);
		i++;
	}
	return (0);
}

static void	parser_sort(char **args)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		i = 0;
		j = 0;
		while (args[i + 1])
		{
			if (ft_strcmp(args[i], args[i + 1]) > 0)
			{
				ft_swap_ptr((void**)&args[i], (void**)&args[i + 1]);
				j = 1;
			}
			i++;
		}
	}
}

int			ft_ls_parser(int ac, char **av, int *flag)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	while (i < ac && av[i][0] == '-' && ft_strcmp("--", av[i]) && \
	!(res = get_flag(av[i], flag)))
		i++;
	if (res > 0)
	{
		ft_ls_error(INVALID_FLAG, &av[i][res]);
		exit(1);
	}
	if (av[i] && !ft_strcmp("--", av[i]))
		i++;
	if (av[i] && av[i + 1])
		parser_sort(&av[i]);
	return (i);
}
