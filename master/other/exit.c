/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:30:08 by hoh               #+#    #+#             */
/*   Updated: 2022/07/27 15:16:51 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global_set	g_set;

int	isdigit_string(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (0 + '0' > *str || 9 + '0' < *str)
			return (0);
		str ++;
	}
	return (1);
}

int	isstring_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (0 + '0' <= str[i] && 9 + '0' >= str[i])
			return (0);
		else
		{
			if (i == 0)
				return (1);
		}
		i ++;
	}
	return (1);
}

void	shell_exit(int status, char *envp[])
{
	errno = status;
	free_arr(envp);
	free(g_set.g_path);
	exit(status);
}

void	exit_shell(char *envp[], char **command)
{
	printf("exit\n");
	if (!command[1])
		shell_exit(0, envp);
	else if (!isdigit_string(command[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", command[1]);
		shell_exit(255, envp);
	}
	else if (command[2])
	{
		printf("minishell: exit: too many arguements\n");
		errno = EPERM;
	}
	else
		shell_exit(ft_atoi(command[1]), envp);
}
