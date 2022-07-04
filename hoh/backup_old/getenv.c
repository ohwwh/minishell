#include "minishell.h"

char	*get_env(t_list *env_list, char *key)
{
	while (env_list)
	{
		if (!ft_strcmp(((char **)env_list->content)[0], key))
			return (((char **)env_list->content)[1]);
		env_list = env_list->next;
	}
	return (0);
}