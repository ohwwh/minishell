#include "minishell.h"

int	redir_in(char **command, char *file, char *envp[])
{
	int fd;

	fd = open(file, O_RDONLY);
	dup2(fd, 0);
	close(fd);
	execute_fork(envp, command);
}

int	redir_in_heredoc(char **command, char *end_str, char *envp[])
{
	char	*pstr;
	char	temp[10] = "temp_file";
	int		fd;

	pstr = 0;
    fd = open(temp, O_RDWR | O_CREAT | O_APPEND, S_IRUSR);
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
	}
	redir_in(command, "./temp_file", envp);
	remove("./temp_file");
}

int	redir_out(char **command, char *file, char *envp[])
{
	int fd;

	fd = open(file, O_WRONLY);
	dup2(fd, 1);
	close(fd);
	execute_fork(envp, command);
}

int	redir_out_double(char **command, char *file, char *envp[])
{
	int fd;

	fd = open(file, O_WRONLY | O_APPEND);
	dup2(fd, 1);
	close(fd);
	execute_fork(envp, command);
}