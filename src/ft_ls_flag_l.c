#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>

static void			flag_l_init(t_flagl *infolen)
{
	infolen->lnk = 0;
	infolen->usr = 0;
	infolen->grp = 0;
	infolen->size = 0;
	infolen->day = 0;
	infolen->hour = 0;
}

static void			get_mtime(time_t t, t_flaglstr *info)
{
	char	**mtime;

	if ((mtime = ft_strsplit(ctime(&t), ' ')))
	{
		info->month = mtime[1];
		info->day = mtime[2];
		mtime[3][5] = '\0';
		mtime[4][4] = '\0';
		info->hour = ((time(0) - t) / 2592000) >= 6 || (time(0) - t) < 0 ? \
		mtime[4] : mtime[3];
		ft_strdel(&mtime[0]);
		if (mtime[4] == info->hour)
			ft_strdel(&mtime[3]);
		else
			ft_strdel(&mtime[4]);
		if (mtime)
			free((void**)mtime);
	}
}

static t_flaglstr	*get_file_info(struct stat *file)
{
	t_flaglstr		*info;
	struct passwd	*pw;
	struct group	*grp;

	errno = 0;
	info = (t_flaglstr*)malloc(sizeof(t_flaglstr));
	if ((pw = getpwuid(file->st_uid)))
	{
		info->usr = ft_strdup(pw->pw_name);
		if ((grp = getgrgid(pw->pw_gid)))
			info->grp = ft_strdup(grp->gr_name);
		else if (!errno)
			info->grp = ft_itoa(file->st_gid);
	}
	else if (errno)
		ft_ls_error(errno, NULL);
	else
	{
		info->usr = ft_itoa(file->st_uid);
		info->grp = ft_itoa(file->st_gid);
	}
	get_mtime(file->st_mtime, info);
	ft_ls_get_permission((long)file->st_mode, info->perm);
	return (info);
}

void				ft_ls_l_infolen(t_finfo **file_tab, t_flagl *infolen)
{
	int		i;
	size_t	res;

	i = 0;
	flag_l_init(infolen);
	while (i != -1 && file_tab[i])
	{
		(file_tab[i])->infostr = get_file_info((file_tab[i])->file);
		if ((res = ft_nbrlen((file_tab[i])->file->st_nlink)) > infolen->lnk)
			infolen->lnk = res;
		if ((res = ft_strlen((file_tab[i])->infostr->usr)) > infolen->usr)
			infolen->usr = res;
		if ((res = ft_strlen((file_tab[i])->infostr->grp)) > infolen->grp)
			infolen->grp = res;
		if ((res = ft_strlen((file_tab[i])->infostr->day)) > infolen->day)
			infolen->day = res;
		if ((res = ft_nbrlen((file_tab[i])->file->st_size)) > infolen->size)
			infolen->size = res;
		if ((res = ft_strlen((file_tab[i])->infostr->hour)) > infolen->hour)
			infolen->hour = res;
		i += ((file_tab[i])->namelen == 0) ? -1 : 1;
	}
}
