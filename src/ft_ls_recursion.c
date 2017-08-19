#include "ft_ls.h"

void	ft_ls_recursion(t_finfo **file_tab, char flag)
{
	int		i;
	char	*path;

	i = 0;
	while (file_tab[i])
	{
		path = (file_tab[i])->path;
		if (S_ISDIR((file_tab[i])->file->st_mode))
		{
			if (ft_strcmp((file_tab[i])->name, ".") && \
			ft_strcmp((file_tab[i])->name, ".."))
			{
				if (path[ft_strlen(path) - 1] == '/')
				{
					path = ft_strjoin_free(path, \
					ft_strjoin((file_tab[i])->name, "/"), 2);
				}
				else
					path = ft_strjoin_free(ft_strjoin(path, "/"), \
					ft_strjoin((file_tab[i])->name, "/"), 3);
				ft_ls_display_switch(path, flag);
				if (path)
					ft_strdel(&path);
			}
		}
		ft_ls_del_finfo(&(file_tab[i]));
		i++;
	}
}
