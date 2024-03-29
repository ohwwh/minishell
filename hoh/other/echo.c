/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:29:59 by hoh               #+#    #+#             */
/*   Updated: 2022/07/27 12:30:00 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nflag(char *arg, int *end)
{
	int			n;
	int			j;

	n = 0;
	if (!(*end) && arg[0] == '-')
	{
		j = 1;
		while (arg[j])
		{
			if (arg[j ++] != 'n')
			{
				*end = 1;
				return (0);
			}
			else
				n ++;
		}
		return (n);
	}
	return (0);
}

static void	write_n(int n)
{
	if (n == 0)
		write(1, "\n", 1);
}

void	echo(char **command)
{
	int	i;
	int	n;
	int	isflag;
	int	end;

	i = 1;
	n = 0;
	end = 0;
	while (command[i])
	{
		if (isflag != -1)
		{
			isflag = nflag(command[i], &end);
			n += isflag;
		}
		if (isflag <= 0)
		{
			ft_putstr_fd(command[i], 1);
			if (command[i + 1])
				write(1, " ", 1);
			isflag = -1;
		}
		i ++;
	}
	write_n(n);
}
