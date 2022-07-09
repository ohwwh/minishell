#include "minishell.h"

void	redir_in(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void    redir_in_heredoc(char *end_str)
{
	char	*pstr;
	char	temp[10] = "temp_file";
	int		fd;

	pstr = 0;
    fd = open(temp, O_RDWR | O_TRUNC);
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
}

void	redir_out(char *file)
{
	int fd;

	fd = open(file, O_WRONLY);
	dup2(fd, 1);
	close(fd);
}

void	redir_out_double(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_APPEND);
	dup2(fd, 1);
	close(fd);
}

void	redir(t_node *node)
{
	if (node->left->type == REDIR)
		redir(node->left);
	if (node->right->data[0][0] == '>')
	{
		if (node->right->data[0][1] == '>')
			redir_out_double(node->right->data[1]);
		else if (!node->right->data[0][1])
			redir_out(node->right->data[1]);
	}
	else if (node->right->data[0][0] == '<')
	{
		if (node->right->data[0][1] == '<')
			redir_in_heredoc(node->right->data[1]);
		else if (!node->right->data[0][1])
			redir_in(node->right->data[1]);
	}
}