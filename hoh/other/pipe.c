#include "minishell.h"

void	front_command(t_node *node, char **envp[], int *fd, int *temp)
{
	dup2(fd[1], 1);
	if (node->left)
		redir(node->left, *envp);
	execute_command(envp, node->right->data, temp);
	shell_exit(0, *envp);
}

void	back_command(t_node *node, char **envp[], int *former_fd, int *fd, int *temp)
{
	if (former_fd)
	{
		dup2(former_fd[1], 1);
		close(former_fd[1]);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	if (node->left)
		redir(node->left, *envp);
	execute_command(envp, node->right->data, temp);
	shell_exit(0, *envp);

}

void	single_command(t_node *node, char **envp[], int *temp)
{
	int	pid;
	const int	built = is_built_in(node->right->data);	

	if (!node)
		return ;
	pid = 0;
	if (!built)
		pid = fork();
	if (pid)
		waitpid(pid, 0, 0);
	else
	{
		if (node->left)
			redir(node->left, *envp);
		execute_command(envp, node->right->data, temp);
		if (!built)
			shell_exit(0, *envp);
	}
}

void	execute_pipe(t_node *node, char **envp[], int *former_fd, int *temp)
{
	int	pipe1;
	int	fd[2];
	int	pid_1;
	int	pid_2;

	pipe1 = pipe(fd);
	pid_1 = fork();
	if (pid_1)
	{
		if (node->left->type == PIPE)
		{
			execute_pipe(node->left, envp, fd, temp);
			close(fd[1]);
			waitpid(pid_1, 0, 0);
		}
		else
		{
			pid_2 = fork();
			if (pid_2)
			{
				close(fd[1]);
				waitpid(pid_2, 0, 0);
				waitpid(pid_1, 0, 0);
			}
			else
				front_command(node->left, envp, fd, temp);
		}
	}
	else
		back_command(node->right, envp, former_fd, fd, temp);
}

void	execute_tree(t_node *node, char **envp[], int *temp)
{
	if (!node->right)
		single_command(node->left, envp, temp);
	else
		execute_pipe(node, envp, 0, temp);
}