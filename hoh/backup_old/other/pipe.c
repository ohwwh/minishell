#include "minishell.h"

extern t_global_set	g_set;

void	execute_pipe_parent(t_node *node, char **envp[], int *fd, int pid_1)
{
	int	pid_2;

	if (node->left->type == PIPE)
	{
		execute_pipe(node->left, envp, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid_1, 0, 0);
	}
	else
	{
		pid_2 = fork();
		if (pid_2)
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid_2, 0, 0);
			waitpid(pid_1, 0, 0);
		}
		else
		{
			//g_set.flag = 1;
			front_command(node->left, envp, fd);
		}
			
	}
}

void	execute_pipe_child(t_node *node, char **envp[], int *fd, int *former_fd)
{
	//g_set.flag = 1;
	if (former_fd)
	{
		dup2(former_fd[1], 1);
		close(former_fd[1]);
		close(former_fd[0]);
	}
	back_command(node->right, envp, fd);
}

void	execute_pipe(t_node *node, char **envp[], int *former_fd)
{
	int	pipe1;
	int	fd[2];
	int	pid_1;
	int	pid_2;

	pipe1 = pipe(fd);
	pid_1 = fork();
	if (pid_1)
	{
		if (former_fd)
		{
			close(former_fd[1]);
			close(former_fd[0]);
		}
		execute_pipe_parent(node, envp, fd, pid_1);
	}
	else
		execute_pipe_child(node, envp, fd, former_fd);
}
