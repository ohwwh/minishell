/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:06:40 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 20:12:15 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree.h"

char	*extract_line(char *s, int *p_from)
{
	int		i;
	char	*res;

	i = *p_from;
	ignore_until_c(s, p_from, s[i]);
	if (s[*p_from] != s[i] || *p_from == i)
		return (NULL);
	if (*p_from - i == 1)
	{
		res = (char *)malloc(sizeof(char));
		res[0] = 0;
	}
	else
		res = ft_substr(s, i + 1, (*p_from)++ - i - 1);
	if (s[i] == '"')
		res = translate(res);
	return (res);
}

char	*extract_word(char *s, int *p_from)
{
	int		i;
	char	*res;

	res = NULL;
	while (s[*p_from] && !is_blank(s[*p_from]) && !is_sep(s[*p_from]))
	{
		if (s[*p_from] == '"' || s[*p_from] == '\'')
			res = join_and_rm_all(res, extract_line(s, p_from));
		else
		{
			i = *p_from;
			while (s[*p_from] && !is_blank(s[*p_from]) \
					&& !is_sep(s[*p_from]) && \
						s[*p_from] != '"' && s[*p_from] != '\'')
				(*p_from)++;
			res = join_and_rm_all(res, ft_substr(s, i, *p_from - i));
		}
	}
	return (translate(res));
}

char	*extract_rd(char *s, int *p_from)
{
	if (s[*p_from] != '<' && s[*p_from] != '>')
		return (NULL);
	if (s[*p_from] == '<' && s[*p_from] == s[*p_from + 1])
	{
		*p_from += 2;
		if (s[*p_from - 2] == '<')
			return (ft_strdup("<<"));
		else
			return (ft_strdup(">>"));
	}
	else
	{
		(*p_from)++;
		if (s[*p_from - 1] == '<')
			return (ft_strdup("<"));
		else
			return (ft_strdup(">"));
	}
}

char	*extract(char *s, int *p_from)
{
	if (s[*p_from] == '\'' || s[*p_from] == '"')
		return (extract_line(s, p_from));
	else if (s[*p_from] && !is_blank(s[*p_from]) && !is_sep(s[*p_from]))
		return (extract_word(s, p_from));
	return (NULL);
}
