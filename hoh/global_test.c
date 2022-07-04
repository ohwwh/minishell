#include "minishell.h"
#include <string.h>

void    redir_in_heredoc(char **command, char *end_str, char *envp[])
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
    remove("./temp_file");
}

int main(void)
{
    redir_in_heredoc(0, "heredoc", 0);
}