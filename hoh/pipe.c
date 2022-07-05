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
		//waitpid(pid, 0, 0);
	}
	//파이프를 실행하려면 -> 부모프로세스가 파이프 뒤에 있는 명령어를 실행해야 함. 
	//부모 프로세스가 앞에 있는 명령어를 실행하면 안되나? exit가 파이프 상에서 실행되는 방식을 볼 때, bash는 이런 식인 것 같다.
	//어차피 뒤의 명령어가 인풋을 받는 명령어라면, 부모 프로세스에서 출력이 있어서 입력으로 들어올 때 까지 기다리지 않나
	//주석처리한 waitpid부분을 넣고 부모프로세스가 command1을 실행하도록 바꿔도 될 것 같다.
}