#include "minishell.h"

extern char *path;

int	isdigit_string(char *str)
{
	while (*str)
	{
		if (0 + '0' > *str || 9 + '0' < *str)
			return (0);
		str ++;
	}
	return (1);
}

int	isstring_string(char *str)
{
	while (*str)
	{
		if (0 + '0' <= *str && 9 + '0' >= *str)
			return (0);
		str ++;
	}
	return (1);
}

void    shell_exit(int status, char *envp[])
{
	errno = status;
	free_arr(envp);
	free(path);
	exit(status);
}

void	exit_shell(char *envp[], char **command)
{
	if (!command[1])
	{
		printf("exit\n");
		shell_exit(0, envp);
	}
	else if (!isdigit_string(command[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", command[1]);
		shell_exit(255, envp);
	}
	else if (command[2])
	{
		printf("minishell: exit: too many arguements\n");
		shell_exit(EPERM, envp);
	}
	else
	{
		printf("exit\n");
		shell_exit(ft_atoi(command[1]), envp);
	}
}