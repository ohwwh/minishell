#include "minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 1);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
	pwd = 0;
}
