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
	char	prompt[100] = "minishell-0.0$ ";
	char	*pstr;
	char	**command;
	t_tree	*tree;
	char	**envp_new;

	struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

	printf("%d\n", getpid());
	init_env(&envp_new, envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		pstr = readline(prompt);
		if (pstr == NULL)
			exit(EXIT_SUCCESS);
		tree = parse(ft_strdup(pstr));
		add_history(pstr);
		if (tree && tree->root)
			shell_pipe(tree->root->left, tree->root->right, &envp_new);
		free(pstr);
		destroy_tree(tree);
		tree = 0;
	}
	free_arr(envp_new);
	free(path);
}
