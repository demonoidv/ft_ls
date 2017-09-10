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
	else if (S_ISSOCK(mode))
		*perm = 's';
	else
		*perm = '-';
}

void		ft_ls_get_permission(long mode, char *perm)
{
	get_file_type(perm, mode);
	perm[1] = (mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (mode & S_IWUSR) ? 'w' : '-';
	if (mode & S_ISUID)
		perm[3] = (mode & S_IXUSR) ? 's' : 'S';
	else
		perm[3] = (mode & S_IXUSR) ? 'x' : '-';
	perm[4] = (mode & S_IRGRP) ? 'r' : '-';
	perm[5] = (mode & S_IWGRP) ? 'w' : '-';
	if (mode & S_ISGID)
		perm[6] = (mode & S_IXGRP) ? 's' : 'S';
	else
	perm[6] = (mode & S_IXGRP) ? 'x' : '-';
	perm[7] = (mode & S_IROTH) ? 'r' : '-';
	perm[8] = (mode & S_IWOTH) ? 'w' : '-';
	if (mode & S_ISVTX)
		perm[9] = (mode & S_IXOTH) ? 't' : 'T';
	else
		perm[9] = (mode & S_IXOTH) ? 'x' : '-';
	perm[10] = '\0';
}
