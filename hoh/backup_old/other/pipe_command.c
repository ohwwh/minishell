#include "minishell.h"

extern t_global_set	g_set;

void	front_command(t_node *node, char **envp[], int *fd)
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (node->left)
		redir(node->left, *envp);
	printf("front\n");
	execute_command(envp, node->right->data);
	shell_exit(0, *envp);
}

void	back_command(t_node *node, char **envp[], int *fd)
{
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	if (node->left)
		redir(node->left, *envp);
	printf("back\n");
	execute_command(envp, node->right->data);
	shell_exit(0, *envp);
}

void	single_command(t_node *node, char **envp[])
{
	int	pid;
	int	built;	

	if (!node)
		return ;
	if (node->right)
		built = is_built_in(node->right->data);
	else
		built = 1;
	pid = 0;
	if (!built)
		pid = fork();
	if (pid)
		waitpid(pid, 0, 0);
	else
	{
		//g_set.flag = 1;
		if (node->left)
			redir(node->left, *envp);
		if (node->right)
		{
			execute_command(envp, node->right->data);
		}
		if (!built)
			shell_exit(0, *envp);
	}
}

void	execute_tree(t_node *node, char **envp[])
{
	if (!node->right)
		single_command(node->left, envp);
	else
		execute_pipe(node, envp, 0);
}
