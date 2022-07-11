#include "minishell.h"

extern t_global_set	g_set;

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

void	init_env(char **envp_new[], char *envp[])
{
	char	**new;
	char	*new_element;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (count_env(envp) + 1));
	while (envp[i])
	{
		new_element = ft_strdup(envp[i]);
		new[i] = new_element;
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			new_element = envp[i];
			while (*(envp[i]) != '=')
				(envp[i])++;
			(envp[i])++;
			g_set.g_path = ft_strdup(envp[i]);
			envp[i] = new_element;
		}
		if (!g_set.g_path || !new_element)
			ft_clear(new, i);
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
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_set.temp[0] = dup(0);
	g_set.temp[1] = dup(1);
	init_env(envp_new, envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
