/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_get_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:37:57 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/12 19:26:41 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <limits.h>
#include <pwd.h>
#include <grp.h>

static void		get_slink_major_minor(t_file *file, char *path)
{
	int			i;
	char		lnk[1000];

	if (S_ISLNK(file->mode))
	{
		if ((i = readlink(path, lnk, 1000)) == -1)
			ft_ls_error(errno, file->name);
		else
		{
			lnk[i] = '\0';
			file->name = ft_strjoin_free(file->name, ft_strjoin(" -> ", lnk), \
			3);
		}
		file->major = 0;
		file->minor = 0;
	}
	else if (file->dev && (file->perm[0] == 'b' || file->perm[0] == 'c'))
	{
		file->minor = MINOR(file->dev);
		file->major = MAJOR(file->dev);
	}
}

static void		get_usr_grp_name(struct stat *st, t_file *file)
{
	struct passwd	*pw;
	struct group	*grp;

	errno = 0;
	if ((pw = getpwuid(st->st_uid)))
		file->usr = ft_strdup(pw->pw_name);
	else if (errno)
		ft_ls_error(errno, NULL);
	else
		file->usr = ft_itoa(st->st_uid);
	if ((grp = getgrgid(st->st_gid)))
			file->grp = ft_strdup(grp->gr_name);
	else if (errno)
		ft_ls_error(errno, NULL);
	else
		file->grp = ft_itoa(st->st_gid);
}

static void		get_mtime(time_t t, t_file *file)
{
	char	**mtime;

	if (t > INT_MAX && (mtime = ft_ls_get_time(t)))
	{
		file->month = mtime[0];
		file->day = mtime[1];
		file->hour = mtime[2];
		ft_memdel((void**)&mtime);
	}
	else if ((mtime = ft_strsplit(ctime(&t), ' ')))
	{
		file->month = mtime[1];
		file->day = mtime[2];
		mtime[3][5] = '\0';
		mtime[4][4] = '\0';
		file->hour = ((time(0) - t) / 2592000) >= 6 || \
		(time(0) - t) < 0 ? mtime[4] : mtime[3];
		ft_strdel(&mtime[0]);
		if (mtime[4] == file->hour)
			ft_strdel(&mtime[3]);
		else
			ft_strdel(&mtime[4]);
		ft_memdel((void**)&mtime);
	}
}

static t_file	*load_file_info(int flag, struct stat *st, t_file *file, \
char *path)
{
	if (FLAG_U_LOW(flag))
	{
		file->mtime = st->st_atime;
		file->nsec = st->st_atimespec.tv_nsec;
	}
	else if (FLAG_C_LOW(flag))
	{
		file->mtime = st->st_ctime;
		file->nsec = st->st_ctimespec.tv_nsec;
	}
	else if (FLAG_U_UP(flag))
	{
		file->mtime = st->st_birthtime;
		file->nsec = st->st_birthtimespec.tv_nsec;
	}
	else
	{
		file->mtime = st->st_mtime;
		file->nsec = st->st_mtimespec.tv_nsec;
	}
	file->mode = st->st_mode;
	file->sympath = NULL;
	file->size = ft_ulltoa_base(st->st_size, 10);
	if (FLAG_L_LOW(flag))
	{
		ft_ls_get_permission(st->st_mode, file->perm, path);
		get_usr_grp_name(st, file);
		file->nlink = st->st_nlink;
		get_mtime(file->mtime, file);
	}
	else
	{
		ft_bzero(file->perm, 11);
		file->usr = NULL;
		file->grp = NULL;
		file->nlink = 0;
		file->month = NULL;
		file->day = NULL;
		file->hour = NULL;
	}
	if (S_ISDIR(file->mode) && FLAG_D_LOW(flag))
		file->mode = (file->mode ^ S_IFDIR) & S_IFREG;
	return (file);
}

t_file			*ft_ls_get_file(int flag, char *path)
{
	t_file		*file;
	struct stat	st;

	file = NULL;
	if (!ft_ls_check_path(path) && (file = (t_file*)malloc(sizeof(t_file))))
	{
		if (!lstat(path, &st))
		{
			if (ISARGFILE(flag))
				file->name = ft_strdup(path);
			else
				file->name = ft_ls_getname_inpath(path);
			file->dev = (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode)) ? \
			st.st_rdev : 0;
			file = load_file_info(flag, &st, file, path);
			file->block = st.st_blocks;
			file->perm_den = 0;
			file->err = 0;
			if (FLAG_L_LOW(flag))
				get_slink_major_minor(file, path);
			ft_strdel(&path);
			return (file);
		}
		file->name = ft_ls_getname_inpath(path);
		ft_strdel(&path);
		file->perm_den = errno;
	}
	return (file);
}
