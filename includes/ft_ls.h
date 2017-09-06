/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:24:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/06 16:08:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>

# define INVALID_FLAG 0
# define FLAG_L_LOW(n) (n & 1)
# define FLAG_R_UP(n) (n & 2)
# define FLAG_A_LOW(n) (n & 4)
# define FLAG_R_LOW(n) (n & 8)
# define FLAG_T_LOW(n) (n & 16)
# define ISARGFILE(n) (n & 32)
# define ISFIRST(n) (n & 64)
# define ISFILE(n) (n & 128)
# define MAJOR(dev) ((dev >> 24) & 0xff)
# define MINOR(dev) (dev & 0xffffff)
# define USAGE "usage: ft_ls [-Ralrt] [file ...]"

typedef struct		s_file
{
	char			*name;
	char			perm[11];
	char			*usr;
	char			*grp;
	char			*month;
	char			*day;
	char			*hour;
	char			*size;
	int				major;
	int				minor;
	int				nlink;
	long			mtime;
	long			nsec;
	int				mode;
	size_t			block;
	dev_t			dev;
}					t_file;

typedef struct		s_dir
{
	int				flag;
	int				perm_den;
	char			*path;
	t_file			**file;
}					t_dir;

typedef struct		s_infolen
{
	size_t			lnk;
	size_t			usr;
	size_t			grp;
	size_t			size;
	size_t			day;
	size_t			hour;
	size_t			major;
	size_t			minor;
}					t_infolen;

int					ft_ls_parser(int ac, char **av, int *flag);
int					ft_ls_check_path(char *path);
void				ft_ls_error(int err_flag, char *str);
void				ft_ls_sort(t_file **tab, int flag);
void				ft_ls_sort_arg(t_file **tab);
void				ft_ls_recursion(t_dir *dir);
void				ft_ls_del_file(t_file **file);
void				ft_ls_del_dir(t_dir *dir);
void				ft_ls_display_switch(t_dir *dir);
void				ft_ls_get_permission(long mode, char *perm);
void				ft_ls_get_infolen(t_file **tab, t_infolen *infolen);
char				*ft_ls_getname_inpath(char *path);
t_dir				*ft_ls_get_dir(int flag, char *path, t_file **tab);
t_file				*ft_ls_get_file(int flag, char *path);
size_t				ft_countfindir(char *path);


#endif
