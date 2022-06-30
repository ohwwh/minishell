#include "minishell.h"

int	pwd(char **command)
{
	char *pwd;

	command = 0;
	pwd = getcwd(0, 1);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
	pwd = 0;
	return (0);
}