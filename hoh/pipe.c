#include "minishell.h"

int	shell_pipe(char **command1, char **command2, char *envp[])
{
	int	fd[2];
	int	pipe1;
	int	pid;

	pipe1 = pipe(fd);
	pid = fork();
	if (!pid)
	{
		dup2(fd[1], 1);
		execute_fork(command1, envp);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		execute_fork(command2, envp);
	}
	//파이프를 실행하려면 -> 부모프로세스가 파이프 뒤에 있는 명령어를 실행해야 함. 
}