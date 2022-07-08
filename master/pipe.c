#include "minishell.h"

/*int	shell_pipe(char **command1, char **command2, char *envp[])
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
}*/

/*int	shell_pipe(char **command1, char **command2, char *envp[])
{
	int	fd[2];
	int	pipe1;
	int	pid;

	pipe1 = pipe(fd);
	pid = fork();
	if (pid)
	{
		dup2(fd[1], 1);
		execute_fork(command1, envp);
		waitpid(pid, 0, 0);
	}  부모 프로세스는 여기서 대기. 아니 그런데, excute_fork에서 만약 execve가 실행되면 waitpid고 나발이고 없는거 아님?
	자식 두개를 연달아 생성해야 되나?
	else
	{
		dup2(fd[0], 0); 자식 프로세스는 만약 입력 대기를 받는 프로그램이라면 여기서 대기. 
		close(fd[1]);
		execute_fork(command2, envp);
	}
	수정 버전

	다중 파이프는 어떻게 구현함?
	*/

void	shell_pipe(t_node *left, t_node *right, char *envp[])
{
	int	fd[2];
	int	pipe1;
	int	pid_1;
	int	pid_2;

	if (!right)
	{
		execute_command(&envp, left->data);
		return ;
	}
	// 이럴거면 루트 노드에 무조건 pipe를 둔 이유가 없지 않나요
	pipe1 = pipe(fd);
	pid_2 = fork();
	if (pid_2)
	{
		pid_1 = fork();
		if (!pid_1)
		{
			dup2(fd[1], 1);
			execute_fork(left->data, envp);
		}
		else
		{
			waitpid(pid_1, 0, 0);
			waitpid(pid_2, 0, 0);
		}
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		if (right->type == PIPE)
			shell_pipe(right->left, right->right, envp);
			
		else
			execute_fork(right->data, envp);
	}
}