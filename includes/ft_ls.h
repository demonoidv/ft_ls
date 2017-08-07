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
# define FLAG_ALL 0b00011111
# define INVALID_FLAG 0
# define ISDIR 040000
# define USAGE "usage: ft_ls [-Ralrt] [file ...]"

typedef struct		s_finfo
{
	int				first;
	char			*path;
	char			*name;
	size_t			namelen;
	struct stat		*file;
}					t_finfo;

int					ft_ls_parser(int ac, char **av, char *flag);
int					ft_ls_check_path(char *path);
void				ft_ls_error(int err_flag, char *str);
void				ft_ls_sort(t_finfo **file_tab, char flag);
void				ft_ls_recursion(t_finfo **file_tab, char flag);
void				ft_ls_del_finfo(t_finfo **file);
void				ft_ls_delall_finfo(t_finfo **file);
void				ft_ls_display_switch(char *path, char flag);
void				ft_ls_display_file(t_finfo *file, char flag);
size_t				ft_countfindir(char *path);
t_finfo				*ft_ls_new_finfo(struct dirent *file, char *path);


#endif
