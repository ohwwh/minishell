#include "minishell.h"

t_global_set	g_set;

int	is_built_in(char **command)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(command[0], "cd"))
		ret = 1;
	else if (!ft_strcmp(command[0], "echo"))
		ret = 1;
	else if (!ft_strcmp(command[0], "env"))
		ret = 1;
	else if (!ft_strcmp(command[0], "exit"))
		ret = 1;
	else if (!ft_strcmp(command[0], "export"))
		ret = 1;
	else if (!ft_strcmp(command[0], "pwd"))
		ret = 1;
	else if (!ft_strcmp(command[0], "unset"))
		ret = 1;
	else if (!ft_strcmp(command[0], "getpid"))
		ret = 1;
	return (ret);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i ++]);
	free(arr);
}

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
	}
	if (signum == SIGINT || signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*pstr;
	t_tree	*tree;
	char	**envp_new;

	init_term(&envp_new, envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		dup2(g_set.temp[0], 0);
		dup2(g_set.temp[1], 1);
		pstr = readline("minishell-1.0$ ");
		if (!pstr)
			pstr = "exit";
		tree = parse(ft_strdup(pstr));
		add_history(pstr);
		if (tree)
			execute_tree(tree->root, &envp_new);
		free(pstr);
		destroy_tree(tree);
		tree = 0;
	}
	free_arr(envp_new);
	free(g_set.g_path);
}
