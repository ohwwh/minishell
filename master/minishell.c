#include "minishell.h"

char	*path;

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

int	execute_fork(char *envp[], char **command)
{
	char	**paths;
	char	*org;
	int		i;
	int		flag;
	int		pid;

	i = 0;
	flag = 0;
	errno = 0;
	if (ft_strchr(command[0], '/'))
	{
		if (execve(command[0], command, envp) == -1)
			return (printf("minishell: %s: %s\n", command[0], strerror(errno)));
	}
	paths = get_paths(path, ':', command[0], envp);
	if (!paths)
		errno = 2;
	org = command[0];
	while (paths && paths[i])
	{
		command[0] = paths[i];
		if (execve(paths[i], command, envp) != -1)
		{
			flag = 1;
			break ;
		}
		else
		{
			if (errno != 2)
				break ;
			i ++;
		}
	}
	if (!flag)
		printf("minishell: %s: %s\n", org, strerror(errno));
	free_arr(paths);
	command[0] = org;
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
	else
		execute_fork(*envp, command);
	return (ret);
}

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(int argc, char *argv[], char *envp[])
{
	char	prompt[100] = "minishell-0.0$ ";
	char	*pstr;
	char	**command;
	t_tree	*tree;
	char	**envp_new;
	
	printf("%d\n", getpid());
	init_env(&envp_new, envp);
	signal(SIGINT, handler);
	while (1)
	{
		pstr = readline(prompt);
		//command = ft_split(pstr, ' ');
		tree = parse(translate(pstr));
		//pre_traversal(tree.root, print_info);
		add_history(pstr);
		//execute_command(&envp_new, command);
		shell_pipe(tree->root->left, tree->root->right, &envp_new);
		free(pstr);
		//free_arr(command);
		destroy_tree(tree);
		tree = 0;
	}
	free_arr(envp_new);
	free(path);
}