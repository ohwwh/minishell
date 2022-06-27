#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

int main(void)
{
	char	prompt[100] = "minishell-0.0$ ";
	char	str2[100] = "child: ";
	char	*pstr;
	char	*cstr;
	int 	pid;
	while (1)
	{
		//write(1, str1, 8);
		//printf("parent: ");
		//read(0, str, 5);
		pstr = readline(prompt);
		if (pstr[0] == 's')
		{
			pid = fork();
			if (pid > 0)
			{
				waitpid(pid, 0, 0);
				free(pstr);
			}
			else
				break ;
		}
	}
	//write(1, str2, 7);
	//read(0, str1, 5);
	cstr = readline(str2);
	free(cstr);
}