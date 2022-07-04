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

void    unset_new(char ***envp, char **command)
{
    int i;
    int j;
    int k;
    int idx;
    char    **new;

    i = 1;
    while (command[i])
    {
        idx = is_exist_new(*envp, command[i]);
        if (idx != -1)
        {
            j = 0;
            k = 0;
            new = (char **)malloc(sizeof(char *) * count_env(*envp));
            while ((*envp)[k])
            {
                if (idx != j)
                {
                    new[j] = (*envp)[k];
                    j ++;
                }
                else
                    free((*envp)[k]);
                k ++;   
            }
            new[j] = 0;
            free(*envp);
            *envp = new;
        }
        i ++;
    }
}