#include "minishell.h"

void	front_command(t_node *node, char **envp[], int *fd)
{
	int	temp;

	temp = dup(1);
	dup2(fd[1], 1);
	if (node->left)
		redir(node->left);
	execute_command(envp, node->right->data, temp);
	shell_exit(0, *envp);
}

void	back_command(t_node *node, char **envp[], int *fd)
{
	int	temp;

	if (node->type == PIPE)
		shell_pipe(node->left, node->right, envp);
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		if (node->left)
			redir(node->left);
		execute_command(envp, node->right->data, 0);
		shell_exit(0, *envp);
	}

}

void	single_command(t_node *node, char **envp[])
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
		execute_command(envp, node->right->data, 0);
		if (!built)
			shell_exit(0, *envp);
	}
}

void	shell_pipe(t_node *left, t_node *right, char **envp[])
{
	int	fd[2];
	int	pipe1;
	int	pid_1;
	int	pid_2;

	if (!right)
	{
		single_command(left, envp);
			return ;
	}
	pipe1 = pipe(fd);
	pid_2 = fork();
	if (pid_2)
	{
		pid_1 = fork();
		if (pid_1)
		{	
			close(fd[1]);
			waitpid(pid_2, 0, 0);
			waitpid(pid_1, 0, 0);
		}
		else
			back_command(right, envp, fd);
	}
	else
		front_command(left, envp, fd);
}

/*void	execute_pipe(t_node *node, char **envp[])
{
	if (!node->right)
		
	else
		execute_pipe(node->right, envp);
}*/