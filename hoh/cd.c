#include "minishell.h"



int cd(t_list **env_list, char **command)
{
    char    *home;

    home = get_env(*env_list, "HOME");
    if (!command[1] || command[1][0] == '~')
        chdir(home);
    else if (chdir(command[1]) == -1)
        return (printf("cd: %s: No such file or directory\n", command[1]));
    return (0);
}