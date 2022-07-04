#include "minishell.h"

extern char	*path;

int	count_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i ++]);

	return (i);
}

void	init_env_new(char **envp_new[], char *envp[])
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

int	is_exist_new(char *envp[], char *command)
{
	int	ret;
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		ret = 1;
		while (envp[i][j] && envp[i][j] != '=')
		{
			if (command[j] != envp[i][j])
			{
				ret = -1;
				break ;
			}
			j ++;
		}
		if (ret != -1)
			return (i);
		i ++;
	}
	return (ret);
}

int env_export_new(char ***envp, char **command)
{
	int		i;
	int		idx;
	char	**new;
	char	*new_command;

	i = 1;
	while (command[i])
	{
		if (command[i][0] == '=')
			return (printf("export: '%s': not a valid identifier\n", command[i]));
		idx = 1;
		while (command[i][idx])
		{
			if (command[i][idx] == '=')
				break ;
			idx ++;
		}
		if (command[i][idx] == 0)
			return (1);
		idx = is_exist_new(*envp, command[i]);
		new_command = ft_strdup(command[i]);
		if (idx == -1)
		{
			idx = 0;
			new = (char **)malloc(sizeof(char *) * (count_env(*envp) + 2));
			while ((*envp)[idx])
			{
				new[idx] = (*envp)[idx];
				idx ++;
			}
			new[idx] = new_command;
			new[idx + 1] = 0;
			free(*envp);
			*envp = new;
		}
		else
		{
			free((*envp)[idx]);
			(*envp)[idx] = new_command;
		}
		i ++;
	}
	return (0);
}