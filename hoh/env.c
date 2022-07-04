#include "minishell.h"

extern char *path;

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
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			while (*(envp[i]) != '=')
				(envp[i]) ++;
			(envp[i]) ++;
			path = ft_strdup(envp[i]);
		}
		new[i] = new_element;
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