/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:45:07 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/19 12:47:48 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redir(char *s)
{
	return (ft_strcmp(s, "<<") == 0 || ft_strcmp(s, ">>") == 0 || \
			ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0);
}

bool	is_redir_char(char c)
{
	return (c == '<' || c == '>');
}

int	check_redir(char *s, int *i)
{
	if (s[*i] == s[*i + 1])
		(*i)++;
	if (s[*i + 1] && (is_redir_char(s[*i + 1]) || s[*i + 1] == '|'))
		return (1);
	return (0);
}

int	check_syntax(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			ignore_until_c(s, &i, s[i]);
		if (s[i] == '<' || s[i] == '>')
			check_redir(s, &i);
		i++;
	}
	return (0);
}
