#include "minishell.h"

extern t_global_set	g_set;

int	command_with_path(char *envp[], char **command)
{
	int	errno_org;

	errno = 0;
	if (execve(command[0], command, envp) == -1)
	{
		dup2(g_set.temp[1], 1);
		errno_org = errno;
		if (!chdir(command[0]))
			printf("minishell: %s: is a directory\n", command[0]);
		else
			printf("minishell: %s: %s\n", command[0], strerror(errno_org));
		return (0);
	}
	return (0);
}

int	execute_fork(char *envp[], char **command)
{
	char	**paths;
	char	*org;
	int		i;

	i = 0;
	if (ft_strchr(command[0], '/'))
		return (command_with_path(envp, command));
	paths = get_paths(g_set.g_path, ':', command[0], envp);
	if (!paths)
		errno = 2;
	org = command[0];
	while (paths && paths[i])
	{
		command[0] = paths[i];
		execve(paths[i ++], command, envp);
		if (errno != 2)
			break ;
	}
	dup2(g_set.temp[1], 1);
	if (!paths || !paths[i])
		printf("minishell: %s: command not found\n", org);
	else
		printf("minishell: %s: %s\n", org, strerror(errno));
	free_arr(paths);
	return (0);
}

int	execute_command(char **envp[], char **command)
{
	int	ret;

	ret = 0;
	if (*command == 0)
		return (ret);
	else if (!ft_strcmp(command[0], "cd"))
		cd(*envp, command);
	else if (!ft_strcmp(command[0], "echo"))
		echo(command);
	else if (!ft_strcmp(command[0], "env"))
		env(*envp, command);
	else if (!ft_strcmp(command[0], "exit"))
		exit_shell(*envp, command);
	else if (!ft_strcmp(command[0], "export"))
		env_export(envp, command);
	else if (!ft_strcmp(command[0], "pwd"))
		pwd(command);
	else if (!ft_strcmp(command[0], "unset"))
		unset(envp, command);
	else if (!ft_strcmp(command[0], "getpid"))
		printf("%d\n", getpid());
	else
		execute_fork(*envp, command);
	return (ret);
}
