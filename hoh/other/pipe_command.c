#include "minishell.h"

extern t_global_set	g_set;

void	front_command(t_node *node, char **envp[], int *fd)
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (node->left)
		redir(node->left, *envp);
	execute_command(envp, node->right->data);
	shell_exit(errno, *envp);
}

void	back_command(t_node *node, char **envp[], int *fd)
{
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	if (node->left)
		redir(node->left, *envp);
	execute_command(envp, node->right->data);
	shell_exit(errno, *envp);
}

void	single_command(t_node *node, char **envp[])
{
	int	pid;
	int	built;
	int	status;

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
	{
		waitpid(pid, &status, 0);
		WIFEXITED(status);
		g_set.errno_temp = WEXITSTATUS(status);
	}
	else
	{
		if (node->left)
			redir(node->left, *envp);
		if (node->right)
			execute_command(envp, node->right->data);
		g_set.errno_temp = errno;
		//printf("%d\n", g_set.errno_temp);
		if (!built)
			shell_exit(errno, *envp);
	}
}

void	execute_tree(t_node *node, char **envp[])
{
	if (!node->right)
		single_command(node->left, envp);
	else
		execute_pipe(node, envp, 0);
}
