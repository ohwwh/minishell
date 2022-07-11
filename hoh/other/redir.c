#include "minishell.h"

void	redir_in(char *file, char *envp[])
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		shell_exit(errno, envp);
	}
	dup2(fd, 0);
	close(fd);
}

void	redir_in_heredoc(char *end_str)
{
	char		*pstr;
	const char	temp[9] = "heredoc";
	int			fd;

	pstr = 0;
	fd = open(temp, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		pstr = readline("> ");
		if (!ft_strcmp(pstr, end_str))
		{
			free(pstr);
			break ;
		}
		write(fd, pstr, ft_strlen(pstr));
		write(fd, "\n", 1);
		free(pstr);
		pstr = 0;
	}
	close(fd);
	fd = open(temp, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

void	redir_out_double(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND);
	dup2(fd, 1);
	close(fd);
}

void	redir(t_node *node, char *envp[])
{
	if (node->left && node->left->type == REDIR)
		redir(node->left, envp);
	if (node->data[0][0] == '>')
	{
		if (node->data[0][1] == '>')
			redir_out_double(node->data[1]);
		else if (!node->data[0][1])
			redir_out(node->data[1]);
	}
	else if (node->data[0][0] == '<')
	{
		if (node->data[0][1] == '<')
			redir_in_heredoc(node->data[1]);
		else if (!node->data[0][1])
			redir_in(node->data[1], envp);
	}
}
