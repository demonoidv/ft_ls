/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_permission.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 20:36:12 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/15 22:48:38 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>

static void	get_file_type(char *perm, long mode)
{
	if (S_ISLNK(mode))
		*perm = 'l';
	else if (S_ISBLK(mode))
		*perm = 'b';
	else if (S_ISDIR(mode))
		*perm = 'd';
	else if (S_ISCHR(mode))
		*perm = 'c';
	else if (S_ISFIFO(mode))
		*perm = 'p';
	else if (S_ISSOCK(mode))
		*perm = 's';
	else
		*perm = '-';
}

static void	acl_and_xattr(char *path, char *perm)
{
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		perm[10] = '@';
	else if (acl_get_file(path, ACL_TYPE_EXTENDED))
		perm[10] = '+';
	else
		perm[10] = '\0';
}

void		ft_ls_get_permission(long mode, char *perm, char *path)
{
	get_file_type(perm, mode);
	perm[1] = (mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (mode & S_IWUSR) ? 'w' : '-';
	if (mode & S_ISUID)
		perm[3] = (mode & S_IXUSR) ? 's' : 'S';
	else
		perm[3] = (mode & S_IXUSR) ? 'x' : '-';
	perm[4] = (mode & S_IRGRP) ? 'r' : '-';
	perm[5] = (mode & S_IWGRP) ? 'w' : '-';
	if (mode & S_ISGID)
		perm[6] = (mode & S_IXGRP) ? 's' : 'S';
	else
	perm[6] = (mode & S_IXGRP) ? 'x' : '-';
	perm[7] = (mode & S_IROTH) ? 'r' : '-';
	perm[8] = (mode & S_IWOTH) ? 'w' : '-';
	if (mode & S_ISVTX)
		perm[9] = (mode & S_IXOTH) ? 't' : 'T';
	else
		perm[9] = (mode & S_IXOTH) ? 'x' : '-';
	acl_and_xattr(path, perm);
	perm[11] = '\0';
}
