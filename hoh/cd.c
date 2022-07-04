#include "minishell.h"

static void	set_pwd(char *envp[])
{
	char    *temp;
	char    *temp2;
	int		pwd_idx;

	pwd_idx = is_exist(envp, "PWD");
	if (pwd_idx != -1)
	{
		temp = cut_value(envp[pwd_idx]);
		temp2 = cat_env("OLDPWD", temp);
		free(temp);
		env_export_string(&envp, temp2);
		free(temp2);
		temp = getcwd(0, 1);
		temp2 = cat_env("PWD", temp);
		free(temp);
		env_export_string(&envp, temp2);
		free(temp2);
	}
}

int cd(char *envp[], char **command)
{
	char	*temp;

	if (!command[1])
	{
		temp = get_value(envp, "HOME");
		chdir(temp);
		free(temp);
	}
	else if (command[1][0] == '-')
	{
		if (is_exist(envp, "OLDPWD") == -1)
		{
			printf("minishell: cd: OLDPWD not set\n");
			errno = EPERM;
		}
		else
		{
			temp = get_value(envp, "OLDPWD");
			chdir(temp);
			free(temp);
		}
	}
	else if (chdir(command[1]) == -1)
		return (printf("cd: %s: %s\n", command[1], strerror(errno)));
	set_pwd(envp);
	return (0);
}