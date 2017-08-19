#include "ft_ls.h"

static void	get_file_type(char *perm, long mode)
{
	if (S_ISLNK(mode))
		*perm = 'l';
	else if (S_ISBLK(mode))
		*perm = 'b';
	else if (S_ISDIR(mode))
		*perm = 'd';
	else if (S_ISCHR(mode))
		*perm = 'c';
	else if (S_ISFIFO(mode))
		*perm = 'p';
	else
		*perm = '-';
}

void		ft_ls_get_permission(long mode, char *perm)
{
	get_file_type(perm, mode);
	perm[1] = (mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (mode & S_IWUSR) ? 'w' : '-';
	perm[3] = (mode & S_IXUSR) ? 'x' : '-';
	perm[4] = (mode & S_IRGRP) ? 'r' : '-';
	perm[5] = (mode & S_IWGRP) ? 'w' : '-';
	perm[6] = (mode & S_IXGRP) ? 'x' : '-';
	perm[7] = (mode & S_IROTH) ? 'r' : '-';
	perm[8] = (mode & S_IWOTH) ? 'w' : '-';
	perm[9] = (mode & S_IXOTH) ? 'x' : '-';
	perm[10] = '\0';
}
