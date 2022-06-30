#include "./libohw/includes/libft.h"

t_list env_list;

void    delnode(void *content)
{
    char    **str;

	if (!content)
		return ;
    str = (char **)content;
    free(str[0]);
    free(str[1]);
    free(str);
}

int exit(int status)
{
	ft_lstclear(&env_list, &delnode);
	exit(status);
}