#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	char	prompt[100] = "minishell-0.0$ ";
	char	str2[100] = "child: ";
	char	*pstr;
	char	*cstr;
	int 	pid;

	signal(SIGINT, handler);
	while (1)
	{
		pstr = readline(prompt);
		add_history(pstr);
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
		free(pstr);
	}
	cstr = readline(str2);
	free(cstr);
}