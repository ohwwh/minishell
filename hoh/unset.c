#include "minishell.h"

extern char *path;

void    unset_string(char ***envp, char *command)
{
    int j;
    int k;
    int idx;
    char    **new;

    idx = is_exist(*envp, command);
    if (idx != -1)
    {
        j = 0;
        k = 0;
        new = (char **)malloc(sizeof(char *) * count_env(*envp));
       if (!new)
			shell_exit(ENOMEM, *envp);
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
        if (!ft_strncmp("PATH", command, 4))
        {
            free(path);
            path = 0;
        }
    }
}

void    unset(char ***envp, char **command)
{
    int i;

    i = 1;
    while (command[i])
        unset_string(envp, command[i ++]);
}