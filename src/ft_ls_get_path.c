/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:10:41 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/18 15:52:35 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_ls_get_path(char *path, char *name)
{
	char	*res;
	size_t	len;

	if (!path)
		return (ft_strdup(name));
	len = ft_strlen(path);
	res = NULL;
	if (path[len - 1] != '/')
		res = ft_strjoin_free(ft_strjoin(path, "/"), name, 1);
	else
		res = ft_strjoin(path, name);
	return (res);
}
