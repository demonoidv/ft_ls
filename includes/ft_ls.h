#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>

# define FLAG_L_LOW 0b00010000
# define FLAG_R_UP 0b00001000
# define FLAG_A_LOW 0b00000100
# define FLAG_R_LOW 0b00000010
# define FLAG_T_LOW 0b00000001
# define INVALID_FLAG 0
# define USAGE "usage: ft_ls [-Ralrt] [file ...]"

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			perm[11];
	char			*usr;
	char			*grp;
	char			*month;
	char			*day;
	char			*hour;
	struct stat		*st;
}					t_file;

typedef struct		s_dir
{
	char			flag;
	char			*name;
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
}					t_infolen;

int					ft_ls_parser(int ac, char **av, char *flag);
int					ft_ls_check_path(char *path);
void				ft_ls_error(int err_flag, char *str);
void				ft_ls_sort(t_finfo **file_tab, char flag);
void				ft_ls_sort_arg(t_finfo **file_tab);
void				ft_ls_recursion(t_finfo **file_tab, char flag);
void				ft_ls_del_finfo(t_finfo **file);
void				ft_ls_delall_finfo(t_finfo **file);
void				ft_ls_display_switch(char *path, char flag);
void				ft_ls_display_file(t_finfo *file, char flag, t_flagl *len);
void				ft_ls_get_permission(long mode, char *perm);
void				ft_ls_l_infolen(t_finfo **file_tab, t_flagl *infolen);
size_t				ft_countfindir(char *path);
t_finfo				*ft_ls_new_finfo(struct dirent *file, char *path);


#endif
