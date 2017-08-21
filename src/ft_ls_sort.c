#include "ft_ls.h"

static void		sort_base(t_file **tab)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		i = 0;
		j = 0;
		while (tab[i + 1])
		{
			if (ft_strcmp((tab[i])->name, (tab[i + 1])->name) > 0)
			{
				ft_swap((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
		i++;
		}
	}
}

static void		sort_t(t_file **tab)
{
	int		i;
	int		j;
	time_t	mtime1;
	time_t	mtime2;

	j = 1;
	while (j)
	{
		i = (j = 0);
		while (tab[i + 1])
		{
			mtime1 = (tab[i])->mtime;
			mtime2 = (tab[i + 1])->mtime;
			if (mtime1 < mtime2 || (mtime1 == mtime2 && (tab[i])->nsec < \
			(tab[i + 1])->nsec))
			{
				ft_swap((void**)&(tab[i]), (void**)&(tab[i + 1]));
				j = 1;
			}
			i++;
		}
	}
}

static void		sort_r(t_file **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tab[j])
		j++;
	j--;
	while (i < j)
	{
		ft_swap((void**)&tab[i], (void**)&tab[j]);
		i++;
		j--;
	}
}

void			ft_ls_sort_arg(t_file **tab)
{
	int		i;
	int		j;

	j = 1;
	if (!tab[2])
	{
		if (S_ISDIR((tab[0])->mode) && \
		!S_ISDIR((tab[1])->mode))
			ft_swap((void**)&(tab[0]), (void**)&(tab[1]));
	}
	else
	{
		while (j)
		{
			j = 0;
			i = 0;
			while (tab[i + 1])
			{
				if (S_ISDIR((tab[i])->mode) && \
				!S_ISDIR((tab[i + 1])->mode))
				{
					ft_swap((void**)&(tab[i]), (void**)&(tab[i + 1]));
					j = 1;
				}
				i++;
			}
		}
	}
}

void			ft_ls_sort(t_file **tab,  int flag)
{
	if (tab[1])
	{
		sort_base(tab);
		if ((FLAG_T_LOW(flag)))
			sort_t(tab);
		if ((FLAG_R_LOW(flag)))
			sort_r(tab);
	}
}
