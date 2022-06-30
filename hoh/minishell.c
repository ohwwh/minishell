#include "minishell.h"

char	*path;

void	free_command(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		free(command[i ++]);
	free(command);
}

int	excute_fork(t_list **env_list, char **command)
{
	char	**paths;
	int		i;
	int		pid;

	i = 0;
	pid = fork();
	if (pid)
	{
		paths = ft_split(path, ':');
		while (paths[i])
		{
			if (execve(paths[i], command, 0) == -1)
				i ++;
		}
		free_command(paths);
	}
	return (0);
}

int	execute_command(t_list **env_list, char **command)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(command[0], "cd"))
		cd(env_list, command);
	else if (!ft_strcmp(command[0], "echo"))
		echo(command);
	else if (!ft_strcmp(command[0], "env"))
		env(env_list, command);
	else if (!ft_strcmp(command[0], "exit"))
		shell_exit(0, env_list);
	else if (!ft_strcmp(command[0], "export"))
		env_export(env_list, command);
	else if (!ft_strcmp(command[0], "pwd"))
		pwd(command);
	else if (!ft_strcmp(command[0], "unset"))
		unset(env_list, command);
	else
		excute_fork(env_list, command);
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

int main(int argc, char *argv[], char *env[])
{
	char	prompt[100] = "minishell-0.0$ ";
	char	str2[100] = "child: ";
	char	*pstr;
	char	**command;
	char	*cstr;
	int 	pid;
	t_list	*env_list;

	printf("%d\n", getpid());
	init_env(&env_list, env);
	signal(SIGINT, handler);
	while (1)
	{
		pstr = readline(prompt);
		command = ft_split(pstr, ' ');
		add_history(pstr);
		execute_command(&env_list, command);
		free(pstr);
		free_command(command);
	}
	ft_lstclear(&env_list, &delnode);
}