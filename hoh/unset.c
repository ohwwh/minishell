#include "minishell.h"

extern char *path;

void    unset(char ***envp, char **command)
{
    int i;
    int j;
    int k;
    int idx;
    char    **new;

    i = 1;
    while (command[i])
    {
        idx = is_exist(*envp, command[i]);
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
                {
                    free((*envp)[k]);
                    idx --;
                }
                k ++;   
            }
            new[j] = 0;
            free(*envp);
            *envp = new;
            if (!ft_strncmp("PATH", command[i], 4))
            {
                free(path);
                path = 0;
            }
        }
        i ++;
    }
}