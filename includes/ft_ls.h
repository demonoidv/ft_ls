/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:24:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/19 18:17:58 by vsporer          ###   ########.fr       */
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
# define SET_ERR 0
# define GET_ERR 1
# define FLAG_L_LOW(n) (n & 1)
# define FLAG_R_UP(n) (n & 2)
# define FLAG_A_LOW(n) (n & 4)
# define FLAG_R_LOW(n) (n & 8)
# define FLAG_T_LOW(n) (n & 16)
# define ISARGFILE(n) (n & 32)
# define ISFIRST(n) (n & 64)
# define ISFILE(n) (n & 128)
# define FLAG_ONE(n) (n & 256)
# define FLAG_U_LOW(n) (n & 512)
# define FLAG_C_LOW(n) (n & 1024)
# define FLAG_U_UP(n) (n & 2048)
# define FLAG_S_UP(n) (n & 4096)
# define FLAG_D_LOW(n) (n & 8192)
# define MAJOR(dev) ((dev >> 24) & 0xff)
# define MINOR(dev) (dev & 0xffffff)

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			*sympath;
	char			perm[12];
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
	size_t			lenmax;
	dev_t			dev;
	int				perm_den;
	int				err;
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
int					ft_ls_symdir(t_file **file, int *error, int flag);
int					ft_ls_return(int flag);
int					ft_ls_check_hfile(t_file **tab, int flag);
int					ft_tablen(t_file **tab, int flag);
void				ft_ls_error(int err_flag, char *str);
void				ft_ls_error_file(t_file **tab, int flag);
void				ft_ls_sort(t_file **tab, int flag);
void				ft_ls_sort_arg(t_file **tab);
void				ft_ls_recursion(t_dir *dir);
void				ft_ls_del_file(t_file **file);
void				ft_ls_del_dir(t_dir *dir);
void				ft_ls_display_switch(t_dir *dir);
void				ft_ls_display_file(int flag, t_file *file, t_infolen *len);
void				ft_ls_get_permission(long mode, char *perm, char *path);
void				ft_ls_file_inline(t_file **tab, int flag);
void				ft_ls_color(char *name, int mode);
void				ft_ls_color_inline(char *name, int mode);
void				ft_ls_time_tostr(time_t t, t_file *file);
void				ft_ls_get_infolen(t_file **tab, t_infolen *infolen,\
					int flag);
char				*ft_ls_getname_inpath(char *path);
char				*ft_ls_get_path(char *path, char *name);
char				**ft_ls_get_time(time_t t);
t_dir				*ft_ls_get_dir(int flag, char *path, t_file **tab);
t_file				*ft_ls_get_file(int flag, char *path);
size_t				ft_ls_count_bloc(t_dir *dir, int flag);
size_t				ft_countfindir(char *path);

#endif
