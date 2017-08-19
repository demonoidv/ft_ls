#include "ft_ls.h"

static void		sort_base(t_finfo **file_tab)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		i = 0;
		j = 0;
		while (file_tab[i + 1])
		{
			if (ft_strcmp((file_tab[i])->name, (file_tab[i + 1])->name) > 0)
			{
				ft_swap((void**)&(file_tab[i]), (void**)&(file_tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}

static void		sort_t(t_finfo **file_tab)
{
	int			i;
	int			j;
	struct stat	*file1;
	struct stat	*file2;

	j = 1;
	while (j)
	{
		i = (j = 0);
		while (file_tab[i + 1])
		{
			file1 = (file_tab[i])->file;
			file2 = (file_tab[i + 1])->file;
			if (file1->st_mtime < file2->st_mtime || (file1->st_mtime == \
			file2->st_mtime && file1->st_mtimespec.tv_nsec < \
			file2->st_mtimespec.tv_nsec))
			{
				ft_swap((void**)&(file_tab[i]), (void**)&(file_tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}

static void		sort_r(t_finfo **file_tab)
{
	size_t	i;
	size_t	j;
//	t_finfo	*tmp;

	i = 0;
	j = 0;
	while (file_tab[j])
		j++;
	j--;
	while (i < j)
	{
		ft_swap((void**)&file_tab[i], (void**)&file_tab[j]);
/*		tmp = file_tab[i];
		file_tab[i] = file_tab[j];
		file_tab[j] = tmp;*/
		i++;
		j--;
	}
}

void			ft_ls_sort_arg(t_finfo **file_tab)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		j = 0;
		i = 0;
		while (file_tab[i + 1])
		{
			if (S_ISDIR((file_tab[i])->file->st_mode) && \
			!S_ISDIR((file_tab[i + 1])->file->st_mode))
			{
				ft_swap((void**)&(file_tab[i]), (void**)&(file_tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}

void			ft_ls_sort(t_finfo **file_tab,  char flag)
{
		sort_base(file_tab);
		if ((flag & FLAG_T_LOW))
			sort_t(file_tab);
		if ((flag & FLAG_R_LOW))
			sort_r(file_tab);
}
