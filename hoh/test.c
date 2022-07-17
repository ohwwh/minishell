#include "minishell.h"

int main(void){
	int fd;
	int	pid;
	char	*str;
	pid = fork();
	if (pid)
	{
		str = readline("parent: ");
		printf("parent: %s\n", str);
		free(str);
		waitpid(pid, 0, 0);
	}
	else
	{
		str = readline("child: ");
		printf("child: %s\n", str);
		free(str);
	}
}