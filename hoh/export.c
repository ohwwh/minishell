#include "minishell.h"

char	*path;

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
	ret[1] = (char *)malloc(sizeof(char) * (j + 1));
	if (!ret[1])
		return (env_split_clear(ret, 2));
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

void    delnode(void *content)
{
    char    **str;

	if (!content)
		return ;
    str = (char **)content;
    free(str[0]);
    free(str[1]);
	str[0] = 0;
	str[1] = 0;
    free(str);
	str = 0;
}

t_list	*is_exist(t_list *env_list, char *key)
{
	t_list	*ret;

	ret = 0;
	while (env_list && ret == 0)
	{
		if (!ft_strcmp(((char **)env_list -> content)[0], key))
		{
			ret = env_list;
			break ;
		}
		env_list = env_list -> next;
	}
	return (ret);
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
		if (!ft_strcmp(content[0], "PATH"))
			path = content[1];
		node = ft_lstnew((void *)content);
		ft_lstadd_back(env_list, node);
		i ++;
	}
}

int env_export(int argc, char *argv[], t_list **env_list)
{
    t_list *node;
    char    **content;
	int		i;


	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '=')
			printf("export: '%s': not a valid identifier\n", argv[i]);
		else
		{
			content = env_split(argv[i]);
			node = is_exist(*env_list, content[0]);
			if (!node)
			{
				node = ft_lstnew((void *)content);
				ft_lstadd_back(env_list, node);
			}
			else
			{
				free(((char **)node->content)[1]);
				((char **)node->content)[1] = content[1];
				if (!ft_strcmp(content[0], "PATH"))
					path = content[1];
				free(content[0]);
				free(content);
			}
		}
		i ++;
	}
	//ft_lstiter(env_list, &print_node);
	//printf("%s\n", path);
    //ft_lstclear(&env_list, &delnode);
	return (0);
}