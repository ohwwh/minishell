/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:06:40 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/08 19:43:17 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

char	*extract_line(char *s, int *p_from)
{
	int		i = *p_from;
	char	*res;

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
	return (res);
}

char	*extract_word(char *s, int *p_from)
{
	int		i;

	i = *p_from;
	while (s[*p_from] && !is_blank(s[*p_from]) && !is_sep(s[*p_from]))
		(*p_from)++;
	if (i == *p_from)
	{
		(*p_from)++;
		return (NULL);
	}
	else
		return (ft_substr(s, i, *p_from - i));
}

char	*extract_$(char *s, int *p_from)
{
	int		i;
	char	*key;
	char	*res;
	char	*dump;

	i = *p_from + 1;
	key = extract_word(s, &i);
	if (key == NULL)
		res = ft_strdup("$");
	else
	{
		dump = ft_strjoin("'", ft_strdup(getenv(key)));
		res = ft_strjoin(dump, "'");
		free(dump);
		free(key);
	}
	*p_from = i;
	return (res);
}

char	*extract_rd(char *s, int *p_from)
{

	if (s[*p_from] != '<' && s[*p_from] != '>')
		return (NULL);
	if (s[*p_from] == '<' && s[*p_from] == s[*p_from + 1])
	{
		*p_from += 2;
		if (s[*p_from] == '<')
			return (ft_strdup("<<"));
		else
			return (ft_strdup(">>"));
	}
	else
	{
		(*p_from)++;
		if (s[*p_from] == '<')
			return (ft_strdup("<"));
		else
			return (ft_strdup(">"));
	}
}

char	*extract(char *s, int *p_from)
{
	if (s[*p_from] == '\'' || s[*p_from] == '"')
		return (extract_line(s, p_from));
	else if (s[*p_from] && !is_blank(s[*p_from]) && !is_sep(s[*p_from]) && s[*p_from] != '$')
		return (extract_word(s, p_from));
	else if (s[*p_from] == '$')
		return (extract_$(s, p_from));
	return (NULL);
}
