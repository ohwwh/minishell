#include "minishell.h"

char	*path;

int	execute_command(int argc, char *argv[], t_list **env_list, char *command)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(command, "cd"))
		cd(argc, argv);
	if (!ft_strcmp(command, "echo"))
		echo(argc, argv);
	if (!ft_strcmp(command, "env"))
		env(argc, argv, env_list);
	if (!ft_strcmp(command, "exit"))
		shell_exit(0, env_list);
	if (!ft_strcmp(command, "export"))
		env_export(argc, argv, env_list);
	if (!ft_strcmp(command, "pwd"))
		pwd(argc, argv);
	if (!ft_strcmp(command, "unset"))
		unset(argc, argv, env_list);
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
	char	*cstr;
	int 	pid;
	t_list	*env_list;

	init_env(&env_list, env);
	signal(SIGINT, handler);
	while (1)
	{
		pstr = readline(prompt);
		add_history(pstr);
		if (pstr[0] == 's')
		{
			pid = fork();
			if (pid > 0)
			{
				waitpid(pid, 0, 0);
				free(pstr);
			}
			else
				break ;
		}
		else
			execute_command(argc, argv, &env_list, pstr);
		free(pstr);
		ft_lstclear(&env_list, &delnode);
	}
	cstr = readline(str2);
	free(cstr);
}