#include "./libohw/includes/libft.h"
#include <stdio.h>

char	**env_split_clear(char **ret, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{	
		free(ret[i]);
		i ++;
	}
	free(ret);
	return (0);
}

char	**env_split_malloc(char *str)
{
	char	**ret;
    int     i;
    int     j;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * 2);
	if (!ret)
		return (0);
    while (str[i] != '=' && str[i ++] != 0);

    ret[0] = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret[0])
		return (env_split_clear(ret, 1));
    if (str[i] == '=')
        i ++;
	j = 0;
    while (str[i ++] != 0)
		j ++;
	if (j)
	{
		ret[1] = (char *)malloc(sizeof(char) * (j + 1));
		if (!ret[1])
			return (env_split_clear(ret, 2));
	}
	else
		ret[1] = 0;
	return (ret);
}

char    **env_split(char *str)
{
	char	**ret;
    int     i;
    int     j;

	i = 0;
	ret = env_split_malloc(str);
	if (!ret)
	return (0);
	while (str[i] != '=' && str[i] != 0)
	{
		ret[0][i] = str[i];
		i ++;
	}
	ret[0][i] = 0;
	if (str[i] == '=')
        i ++;
	j = 0;
    while (str[i] != 0)
	{
		ret[1][j] = str[i];
		i ++;
		j ++;
	}
	if (ret[1])
		ret[1][j] = 0;
	return (ret);
}

void    print_node(void *content)
{
    char **str;

    str = (char **)content;
	printf("%s=", str[0]);
    printf("%s\n", str[1]);
}

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

void	init_env(t_list **env_list, char *env[])
{
	int	i;
	char	**content;
	t_list	*node;

	i = 0;
	while (env[i])
	{
		content = env_split(env[i]);
		node = ft_lstnew((void *)content);
		ft_lstadd_back(env_list, node);
		i ++;
	}
}

int main(int argc, char *argv[], char *env[])
{
    t_list *env_list;
    t_list *node;
    char    **content = 0;
	int		i;

	init_env(&env_list, env);
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '=')
			printf("export: '%s': not a valid identifier\n", argv[i]);
		else
		{
			content = env_split(argv[i]);
			node = ft_lstnew((void *)content);
			ft_lstadd_back(&env_list, node);
		}
		i ++;
	}
	ft_lstiter(env_list, &print_node);
    ft_lstclear(&env_list, &delnode);
}