#include "minishell.h"

void	env(char *envp[], char **command)
{
	int	i;

	i = 0;
	if (command[1])
	{
		errno = EPERM;
		write(1, "env: too many arguments\n", 24);
		return ;
	}
	while (envp[i])
		printf("%s\n", envp[i ++]);
}
