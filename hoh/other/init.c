#include "minishell.h"

extern t_global_set	g_set;

static void	ft_clear(char **ret, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{	
		free(ret[i]);
		i ++;
	}
	free(ret);
	exit(ENOMEM);
}

void	init_shell(char **new, char *envp[], int idx)
{
	char	*pwd;
	char	*shell;

	pwd = getcwd(0, 1);
	shell = ft_strjoin("SHELL=", pwd);
	if (!shell)
		ft_clear(new, idx);
	new[idx] = shell;
	free(pwd);
	pwd = 0;
}

void	init_path(char *envp)
{
	while (*envp != '=')
		envp ++;
	envp ++;
	g_set.g_path = ft_strdup(envp);
}

void	init_env(char **envp_new[], char *envp[])
{
	char	**new;
	char	*new_element;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (count_env(envp) + 1));
	while (envp[i])
	{
		if (!ft_strncmp("SHELL", envp[i], 5))
			init_shell(new, envp, i);
		else
		{
			new_element = ft_strdup(envp[i]);
			new[i] = new_element;
			if (!ft_strncmp("PATH", envp[i], 4))
				init_path(envp[i]);
			if (!g_set.g_path || !new_element)
				ft_clear(new, i);
		}
		i ++;
	}
	new[i] = 0;
	*envp_new = new;
}

void	init_term(char **envp_new[], char *envp[])
{
	struct termios	term;
	char			dummy;

	dummy = 'c';
	g_set.g_path = &dummy;
	g_set.flag = 0;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_set.temp[0] = dup(0);
	g_set.temp[1] = dup(1);
	init_env(envp_new, envp);
}
