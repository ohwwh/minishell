#include "minishell.h"

extern char	*g_path;

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
	char	dummy;

	i = 0;
	dummy = 'c';
	g_path = &dummy;
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
			g_path = ft_strdup(envp[i]);
			envp[i] = new_element;
		}
		if (!g_path || !new_element)
			ft_clear(new, i);
		i ++;
	}
	new[i] = 0;
	*envp_new = new;
}

int	env(char *envp[], char **command)
{
	int	i;

	i = 0;
	if (command[1])
	{
		errno = EPERM;
		return (write(1, "env: too many arguments\n", 24));
	}
	while (envp[i])
		printf("%s\n", envp[i ++]);
	return (0);
}
