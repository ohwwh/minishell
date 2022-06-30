/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:03 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/28 17:14:31 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_envs_len(char *envs[])
{
	int	i;

	i = 0;
	while (envs[i])
		i++;
	return (i);
}

void	set_envs(char *envs[])
{
	int			l;
	int			i;
	const int	size = get_envs_len(envs);
	int			i_e;

	g_envs = (t_map *)malloc((size + 1) * sizeof(t_map));
	if (g_envs == NULL)
		exit_with_error("bad alloc", SYS);
	i_e = 0;
	while (i_e < size)
	{
		l = ft_strlen(*envs);
		i = 0;
		while (*envs[i] && *envs[i] != '=')
			i++;
		g_envs[i_e].key = single_strcpy(envs[i_e], 0, i - 1);
		g_envs[i_e].value = single_strcpy(envs[i_e], i + 1, size - 1);
		i_e++;
	}
	g_envs[i_e].key = NULL;
	g_envs[i_e].value = NULL;
}

void	test_parse(const char *s)
{
	const t_token	*t = tokenize(s);
	int				i;

	i = 0;
	while (t[i].type != NONE)
	{
		printf("str: %s\t", t[i].str);
		if (t[i].type == CMD)
			printf("type: cmd\n");
		else if (t[i].type == ARGS)
			printf("type: word\n");
		else if (t[i].type == PIPE)
			printf("type: pipe\n");
		else if (t[i].type == REDIR)
			printf("type: redirection\n");
		else
			printf("type: none\n");
		i++;
	}
}

int	main(int argc, char *argv[], char *envs[])
{
	set_envs(envs);
	test_parse(argv[1]);
}
