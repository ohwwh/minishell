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
		if (!built)
			shell_exit(errno, *envp);
	}
}

void	tree_heredoc(t_list *queue, char *envp[])
{
	char		*pstr;
	char		*temp;
	char		*end_str;
	int			fd;

	pstr = get_value(envp, "SHELL");
	temp = ft_strjoin(pstr, "/heredoc");
	free(pstr);
	while (queue->len)
	{
		fd = open(temp, O_RDWR | O_CREAT | O_TRUNC, 0644);
		g_set.flag = 2;
		end_str = dequeue(queue);
		while (1)
		{
			pstr = readline("> ");
			if (!pstr || g_set.flag == 3)
			{
				close(fd);
				free(pstr);
				free(temp);
				return ;
			}
			if (!ft_strcmp(pstr, end_str))
			{
				free(pstr);
				break ;
			}
			write(fd, pstr, ft_strlen(pstr));
			write(fd, "\n", 1);
			free(pstr);
			close(fd);
		}
	}
	free(temp);
}

void	execute_tree(t_tree *tree, char **envp[])
{
	tree_heredoc(tree->queue, *envp);
	if (g_set.flag == 3)
		return ;
	if (!tree->root->right)
		single_command(tree->root->left, envp);
	else
		execute_pipe(tree->root, envp, 0);
}
