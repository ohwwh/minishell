#include "minishell.h"

extern char	*path;

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

int	is_valid(char *command)
{
	int	i;

	i = 0;
	if (command[0] == '=')
	{
		errno = EPERM;
		printf("export: '%s': not a valid identifier\n", command);
		return (0);
	}
	while (command[i])
	{
		if (command[i] == '=')
			break ;
		i ++;
	}
	if (command[i] == 0)
		return (0);
	return (1);
}

int	env_export_string(char ***envp, char *command)
{
	int		idx;
	char	**new;
	char	*new_command;

	if (is_valid(command))
	{
		idx = is_exist(*envp, command);
		new_command = ft_strdup(command);
		if (!new_command)
			shell_exit(ENOMEM, *envp);
		if (idx == -1)
		{
			idx = 0;
			new = (char **)malloc(sizeof(char *) * (count_env(*envp) + 2));
			if (!new)
				shell_exit(ENOMEM, *envp);
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
			if (!ft_strncmp("PATH", new_command, 4))
			{
				free(path);
				path = cut_value(new_command, *envp);
			}
			free((*envp)[idx]);
			(*envp)[idx] = new_command;
		}
	}
	return (0);
}

int env_export(char ***envp, char **command)
{
	int		i;

	i = 1;
	while (command[i])
		env_export_string(envp, command[i ++]);
	return (0);
}