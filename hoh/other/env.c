/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:30:03 by hoh               #+#    #+#             */
/*   Updated: 2022/07/27 12:30:04 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char *envp[], char **command)
{
	int	i;

	i = 0;
	if (command[1])
	{
		errno = EPERM;
		write(1, "env: too many arguments\n", 24);
		return ;
	}
	while (envp[i])
		printf("%s\n", envp[i ++]);
}
