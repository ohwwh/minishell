#include "minishell.h"

void    shell_exit(int status, t_list **env_list)
{
	ft_lstclear(env_list, &delnode);
	exit(status);
}