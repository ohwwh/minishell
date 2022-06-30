#include "minishell.h"

t_list env_list;

void    print_env(void *content)
{
	char **str;

	str = (char **)content;
	printf("%s=", str[0]);
	printf("%s\n", str[1]);
}

int env(int argc, char *argv[], t_list **env_list)
{
	int i;

	i = 0;
	if (argc != 1)
		return (write(1, "env: too many arguments\n", 24));
	ft_lstiter(*env_list, &print_env);
	return (0);
}