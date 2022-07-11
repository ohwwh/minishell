#include "minishell.h"

t_global_set	g_set;

int	is_built_in(char **command)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(command[0], "cd"))
		ret = 1;
	else if (!ft_strcmp(command[0], "echo"))
		ret = 1;
	else if (!ft_strcmp(command[0], "env"))
		ret = 1;
	else if (!ft_strcmp(command[0], "exit"))
		ret = 1;
	else if (!ft_strcmp(command[0], "export"))
		ret = 1;
	else if (!ft_strcmp(command[0], "pwd"))
		ret = 1;
	else if (!ft_strcmp(command[0], "unset"))
		ret = 1;
	else if (!ft_strcmp(command[0], "getpid"))
		ret = 1;
	return (ret);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i ++]);
	free(arr);
}

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
	if (!paths || paths[i])
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

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 1);
    }
    if (signum == SIGINT || signum == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
    }
}

int main(int argc, char *argv[], char *envp[])
{
	char	*pstr;
	t_tree	*tree;
	char	**envp_new;
	
	init_term(&envp_new, envp);
	while (1)
	{
		dup2(g_set.temp[0], 0);
		dup2(g_set.temp[1], 1);
		pstr = readline("minishell-1.0$ ");
		if (!pstr)
			pstr = "exit";
		tree = parse(ft_strdup(pstr));
		add_history(pstr);
		if (tree)
			execute_tree(tree->root, &envp_new);
		free(pstr);
		destroy_tree(tree);
		tree = 0;
	}
	free_arr(envp_new);
	free(g_set.g_path);
}