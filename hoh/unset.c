#include "minishell.h"

void	unset(int argc, char *argv[], t_list **env_list)
{
    int i;
	t_list *node;

    i = 1;
    while (i < argc)
    {
        node = is_exist(*env_list, argv[i]);
        if (node)
            ft_lstdelnode(env_list, node, &delnode);
        i ++;
    }
}