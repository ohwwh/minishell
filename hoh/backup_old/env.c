#include "minishell.h"

void    print_env(void *content)
{
	char **str;

	str = (char **)content;
	printf("%s=", str[0]);
	printf("%s\n", str[1]);
}

int env(t_list **env_list, char **command)
{
	if (command[1])
		return (write(1, "env: too many arguments\n", 24));
	ft_lstiter(*env_list, &print_env);
	return (0);
}

int	env_new(char *envp[], char **command)
{
	int	i;
	if (command[1])
		return (write(1, "env: too many arguments\n", 24));
	while (envp[i])
		printf("%s\n", envp[i ++]);
	return (0);
}