#include "minishell.h"

extern char *path;

void    shell_exit(int status, char *envp[])
{
	free_arr(envp);
	free(path);
	exit(status);
}