#include "ft_ls.h"

static size_t	count_bloc(t_finfo **file_tab)
{
	size_t	nb;
	t_finfo	*tmp;

	nb = 0;
	if (file_tab)
	{
		while ((tmp = *file_tab))
		{
			nb += tmp->file->st_blocks;
			file_tab++;
		}
	}
	return (nb);
}

void			ft_ls_display_file(t_finfo *file, char flag)
{
	if (!(flag & FLAG_L_LOW))
		ft_putendl(file->name);
}

static void		print_info_dir(t_finfo *file, char flag)
{
	size_t	nbbloc;

	if (!file->first)
		ft_printf("%s:\n", (*file_tab)->path);
	if ((nbbloc = count_bloc(file_tab)) && (flag & FLAG_L_LOW))
		ft_printf("total %u\n", nbbloc);
}

static void		display_dir(t_finfo **file_tab, char flag)
{
	int		i;

	i = 0;
	print_info_dir(*file_tab, flag);
	if (file_tab)
	{
		ft_ls_sort(file_tab, flag);
		while (file_tab[i])
		{
			if ((file_tab[i])->name[0] == '.')
			{
				if ((flag & FLAG_A_LOW))
					ft_ls_display_file(file_tab[i], flag);
			}
			else
				ft_ls_display_file(file_tab[i], flag);
			i++;
		}
		ft_putendl("");
	}
}

void			ft_ls_display_switch(char *path, char flag)
{
	int				i;
	size_t			tablen;
	t_finfo			**file_tab;
	DIR				*dir;

	i = 0;
	if (path && !ft_ls_check_path(path))
	{
		if ((tablen = ft_countfindir(path)))
			tablen += 1;
		if (!(file_tab = (t_finfo**)malloc((sizeof(t_finfo*) * tablen))))
			ft_ls_error(errno, NULL);
		else if ((dir = (opendir(path))))
		{
			while ((file_tab[i] = ft_ls_new_finfo(readdir(dir), path)))
			{
				i++;
			}
			closedir(dir);
			display_dir(file_tab, flag);
			if ((flag & FLAG_R_UP))
				ft_ls_recursion(file_tab, flag);
		}
		ft_ls_delall_finfo(file_tab);
	}
}
