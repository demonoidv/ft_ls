#include "ft_ls.h"

static size_t	countfile(t_finfo **file_tab)
{
	size_t	nbfile;

	nbfile = 0;
	while (file_tab[nbfile])
		nbfile++;
	return (nbfile);
}

static void		sort_t(t_finfo **file_tab)
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
			if ((file_tab[i])->file->st_mtime < \
			(file_tab[i + 1])->file->st_mtime)
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
	t_finfo	*tmp;

	i = 0;
	j = (countfile(file_tab) - 1);
	while (i < j)
	{
		tmp = file_tab[i];
		file_tab[i] = file_tab[j];
		file_tab[j] = tmp;
		i++;
		j--;
	}
}

void			ft_ls_sort(t_finfo **file_tab,  char flag)
{
		if ((flag & FLAG_T_LOW))
			sort_t(file_tab);
		if ((flag & FLAG_R_LOW))
			sort_r(file_tab);
}
