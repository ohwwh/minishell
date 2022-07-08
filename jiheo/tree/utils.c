/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:28:30 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/08 19:31:04 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\r' || c == '\n' || c == '\a' || c == '\t');
}

bool	is_sep(char c)
{
	return (is_blank(c) || c == '>' || c == '<' || c =='|');
}

void	ignore_space(char *s, int *i)
{
	while (s[*i] && is_blank(s[*i]))
		(*i)++;
}

// s[*i] == c
void	ignore_until_c(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
}

char	*translate(char *s)
{
	char	*tmp;
	int		i;
	int		s_i;
	char	*res;
	char	*dump;

	i = 0;
	res = NULL;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '$')
			tmp = extract(s, &i);
		else
		{
			s_i = i;
			while (s[i] && !(s[i] == '\'' || s[i] == '$'))
				i++;
			tmp = ft_substr(s, s_i, i - s_i);
		}
		dump = res;
		res = ft_strjoin(res, tmp);
		free(dump);
		free(tmp);
	}
	return (res);
}
