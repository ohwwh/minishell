#include "minishell.h"

void	unset(t_list **env_list, char **command)
{
    int i;
	t_list *node;

    i = 0;
    while (command[i])
    {
        node = is_exist(*env_list, command[i]);
        if (node)
            ft_lstdelnode(env_list, node, &delnode);
        i ++;
    }
}